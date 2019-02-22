/* Simulator for datalink protocols. 
 *    Written by Andrew S. Tanenbaum.
 *    Revised by Shivakant Mishra.
 *    Revised by Christophe Deleuze.
 */


#include <sys/poll.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "simulator.h"

extern void sim_error(char *s);


#define NR_TIMERS 8             /* number of timers; this should be equal
                                   to number of sender buffers. */
#define MAX_QUEUE 100000        /* max number of buffered frames */
#define NO_EVENT -1             /* no event possible */
#define FRAME_SIZE (sizeof(frame))
#define BYTE 0377               /* byte mask */
#define UINT_MAX  0xFFFFFFFF    /* maximum value of an unsigned 32-bit int */
#define INTERVAL 100000         /* interval for periodic printing */
#define AUX 2                   /* aux timeout is main timeout/AUX */

/* DEBUG MASKS */
#define DBG_SENDS        0x0001 /* frames sent */
#define DBG_RECEIVES     0x0002 /* frames received */
#define DBG_TIMEOUTS     0x0004 /* timeouts */
#define DBG_PERIODIC     0x0008 /* periodic printout for use with long runs */
#define DBG_TIMERS       0x0010

/* Status variables used by the workers, M0 and M1. */
bigint ack_timer[NR_TIMERS];    /* ack timers */
uint_t seqs[NR_TIMERS];   /* last sequence number sent per timer */
bigint lowest_timer;            /* lowest of the timers */
bigint aux_timer;               /* value of the auxiliary timer */
uint_t timedout_seq = NR_TIMERS;  /* tells which frame timed out */
uint_t timedout_buf;

frame last_frame;               /* arrive frames are kept here */
int offset;                     /* to prevent multiple timeouts on same tick*/
bigint tick;                    /* current time */
int retransmitting;             /* flag that is set on a timeout */

char *tag[] = {"Data", "Ack ", "Nak "};

/* network layer */
int network_layer_status;       /* 0 is disabled, 1 is enabled */
unsigned int next_net_pkt;      /* seq of next network packet to fetch */
unsigned int last_pkt_given= 0xFFFFFFFF;        /* seq of last pkt delivered*/

/* Statistics */
int data_sent;                  /* number of data frames sent */
int data_retransmitted;         /* number of data frames retransmitted */
int data_lost;                  /* number of data frames lost */
int data_not_lost;              /* number of data frames not lost */
int good_data_recd;             /* number of data frames received */
int cksum_data_recd;            /* number of bad data frames received */

int acks_sent;                  /* number of ack frames sent */
int acks_lost;                  /* number of ack frames lost */
int acks_not_lost;              /* number of ack frames not lost */
int good_acks_recd;             /* number of ack frames received */
int cksum_acks_recd;            /* number of bad ack frames received */

int payloads_accepted;          /* number of pkts passed to network layer */
int timeouts;                   /* number of timeouts */
int ack_timeouts;               /* number of ack timeouts */

/* Incoming frames are buffered here for later processing. */
frame queue[MAX_QUEUE];         /* buffered incoming frames */
frame *inp  = &queue[0];        /* where to put the next frame */
frame *outp = &queue[0];        /* where to remove the next frame from */
int nframes;                    /* number of queued frames */

/* Prototypes. */

uint_t get_timedout_seqnr(void);
uint_t get_timedout_buf(void);
void wait_for_event(event_type *event);

void from_network_layer(packet *p);
void to_network_layer(packet *p);
void from_physical_layer(frame *r);
void to_physical_layer(frame *s);
void start_timer(uint_t seq, uint_t b);
void stop_timer(uint_t);
void start_ack_timer(void);
void stop_ack_timer(void);
void enable_network_layer(void);
void disable_network_layer(void);
int check_timers(void);
int check_ack_timer(void);
uint_t pktnum(packet *p);
void recalc_timers(void);

static void queue_frames(void);
static int pick_event(void);
static event_type frametype(void);
static void dump_timers(void);
static void print_statistics(void);

typedef enum
     { sent_frame, lost_frame, good_frame, bad_frame, 
       timer_expired, ack_timer_expired } pevent;


static
void print_frame(frame* f, char *pf)
{
  char pf2[40];
  
  if (!f) { pf=NULL; return; }
  
  if (f->kind==data) 
    sprintf(pf2, " %s %d %d \"%d\" ",
	    tag[f->kind], f->seq, f->ack, pktnum(&f->info));
  else
    sprintf(pf2, " %s %d ", tag[f->kind], f->ack);
  sprintf(pf, "%-14s", pf2);
}


static 
void print_event(pevent pe, frame* fr)
{
  char message[80];
  char pf[40];
  
  print_frame(fr, pf);
  
  if (!id) 
    switch(pe) {
    case sent_frame: sprintf(message, "\t\t %s --> ", pf); break;
    case lost_frame: sprintf(message, "\t\t %s -->*", pf); break;
    case good_frame: sprintf(message, "\t\t  <-- %s", pf); break;
    case bad_frame:  sprintf(message, "\t\t *<-- %s", pf); break;
    case timer_expired:sprintf(message,"Timeout(%i)",timedout_seq);break;
    case ack_timer_expired: sprintf(message, " Ack timeout"); break;
    }
  else
    switch(pe) {
    case sent_frame: sprintf(message, " <-- %s", pf); break;
    case lost_frame: sprintf(message, "*<-- %s", pf); break;
    case good_frame: sprintf(message, "%s --> ", pf); break;
    case bad_frame:  sprintf(message, "%s -->*", pf); break;
    case timer_expired:sprintf(message, "\t\t\tTimeout(%i)",timedout_seq); break;
    case ack_timer_expired: sprintf(message, "\t\t\tAck timeout"); break;
    }
  
  if (!id) printf("%5lu %s%s%s", tick/DELTA,
		  "", 0?"\t\t":"", message);
  else printf("%5lu %s %s \t\t\t\t  %s", tick/DELTA,
	      "", 0?"\t\t":"", message);
  if (debug_flags & DBG_TIMERS) dump_timers();
  putchar('\n');
}



/* ---- workers's library */

void wait_for_event(event_type *event)
{
/* Wait_for_event reads frames on the pipe from the other worker, if
 * any.  If so, it puts them in the queue array.  It then gets time
 * from main and makes a decision about what to do next.
 */
 
  bigint ct, word = OK;

  offset = 0;			/* prevents two timeouts at the same tick */
  retransmitting = 0;		/* counts retransmissions */

  while (true) {
    queue_frames();		/* go get any newly arrived frames */

    if (write(mwfd, &word, TICK_SIZE) != TICK_SIZE) sim_error("write");
    if (read(mrfd, &ct, TICK_SIZE) != TICK_SIZE) sim_error("read");
    if (ct == 0) print_statistics();

    tick = ct;		/* update time */

    if ((debug_flags & DBG_PERIODIC) && (tick%INTERVAL == 0))
      printf("Tick %lu. Proc %c. Data sent=%d  Payloads accepted=%d "
	     "Timeouts=%d\n", tick/DELTA, id?'B':'A', 
	     data_sent, payloads_accepted, timeouts);
    
    /* Now pick event. */
    *event = pick_event();
    if (*event == NO_EVENT) {
      word = (lowest_timer == 0 ? NOTHING : OK);
      continue;
    }
    word = OK;
    if (*event == timeout) {
      timeouts++;
      retransmitting = 1;	/* enter retransmission mode */
      if (debug_flags & DBG_TIMEOUTS)
	print_event(timer_expired, NULL);
    }
    
    if (*event == ack_timeout) {
      ack_timeouts++;
      if (debug_flags & DBG_TIMEOUTS)
	print_event(ack_timer_expired, NULL);
    }
    return;
  }
}

/* See if any frames from the peer have arrived; if so get and queue them.
 * Queue_frames() sucks frames out of the pipe into the circular buffer,
 * queue[].
 */
void queue_frames(void)
{
  int prfd, ar;
  struct pollfd pollbuf[1];

  prfd = (id == 0 ? r2 : r1);	/* which file descriptor is pipe on */

  pollbuf[0].fd = prfd;
  pollbuf[0].events = POLLIN;
  pollbuf[0].revents = 0;

  while (poll(pollbuf, 1, 0)==1) {
    if ((ar = read(prfd, inp, FRAME_SIZE)) != FRAME_SIZE)
      sim_error("Error reading frame from peer");
    inp++;
    if (inp == outp)
      sim_error("Out of queue space. Increase MAX_QUEUE and re-make.");
    nframes++;
    if (inp == &queue[MAX_QUEUE]) inp = queue;
  }
}


int pick_event(void)
{
/* Pick a random event that is now possible for the process.
 * Note that the order in which the tests is made is critical, as it gives
 * priority to some events over others.  For example, for protocols 3 and 4
 * frames will be delivered before a timeout will be caused.  This is probably
 * a reasonable strategy, and more closely models how a real line works.
 */

  if (check_ack_timer() > 0) return(ack_timeout);
  if (nframes > 0) return((int)frametype());
  if (network_layer_status && (!id || duplex)) return(network_layer_ready);
  if (check_timers() >= 0) return(timeout);	/* timer went off */
  return(NO_EVENT);
}


event_type frametype(void)
{
/* This function is called after it has been decided that a frame_arrival
 * event will occur.  The earliest frame is removed from queue[] and copied
 * to last_frame.  This copying is needed to avoid messing up the simulation
 * in the event that the protocol does not actually read the incoming frame.
 * For example, in protocols 2 and 3, the senders do not call
 * from_physical_layer() to collect the incoming frame. If frametype() did
 * not remove incoming frames from queue[], they never would be removed.
 * Of course, one could change sender2() and sender3() to have them call
 * from_physical_layer(), but doing it this way is more robust.
 *
 * This function determines (stochastically) whether the arrived frame is good
 * or bad (contains a checksum error).
 */

  int n, i;
  event_type event;

  /* Remove one frame from the queue. */
  last_frame = *outp;		/* copy the first frame in the queue */
  outp++;
  if (outp == &queue[MAX_QUEUE]) outp = queue;
  nframes--;

  /* Generate frames with checksum errors at random. */
  n = rand () % 1001;
  if (n < garbled) {
	/* Checksum error.*/
	event = cksum_err;
	if (last_frame.kind == data) cksum_data_recd++;
	if (last_frame.kind == ack) cksum_acks_recd++;
	i = 0;
  } else {
	event = frame_arrival;
	if (last_frame.kind == data) good_data_recd++;
	if (last_frame.kind == ack) good_acks_recd++;
	i = 1;
  }

  if (debug_flags & DBG_RECEIVES) {
    print_event((i?good_frame:bad_frame), &last_frame);
  }
  return(event);
}

  
void from_physical_layer (frame *r)
{
/* Copy the newly-arrived frame to the user. */
 *r = last_frame;
}
					

void to_physical_layer(frame *s)
{
/* Pass the frame to the physical layer for writing on pipe 1 or 2. 
 * However, this is where bad packets are discarded: they never get written.
 */

  int fd, got, k;

  if (s->kind == data) data_sent++;
  if (s->kind == ack) acks_sent++;
  if (retransmitting) data_retransmitted++;

  /* Bad transmissions (checksum errors) are simulated here. */
  k = rand () % 1001;
  if (k < pkt_loss) {	/* simulate packet loss */
	if (debug_flags & DBG_SENDS) {
		print_event(lost_frame, s);
	}
	if (s->kind == data) data_lost++;	/* statistics gathering */
	if (s->kind == ack) acks_lost++;	/* ditto */
	return;

  }
  if (s->kind == data) data_not_lost++;		/* statistics gathering */
  if (s->kind == ack) acks_not_lost++;		/* ditto */
  fd = (id == 0 ? w1 : w2);

  got = write(fd, s, FRAME_SIZE);
  if (got != FRAME_SIZE) sim_error("to_phy");	/* must be done */

  if (debug_flags & DBG_SENDS) {
	  print_event(sent_frame, s);
  }
}

/* ---- timer-related functions */

unsigned int get_timedout_seqnr(void)
{
  return(timedout_seq);
}

unsigned int get_timedout_buf(void)
{
  return(timedout_buf);
}

void start_timer(uint_t seq, uint_t b)
{
/* Start a timer for a data frame. */

  ack_timer[b] = tick + timeout_interval + offset;
  seqs[b] = seq;
  offset++;
  recalc_timers();		/* figure out which timer is now lowest */
}

void stop_timer(uint_t seq)
{
/* Stop a data frame timer. */
  int i;

  for (i = 0; i < NR_TIMERS; i++)
    if (seqs[i] == seq) { 
      ack_timer[i] = 0;
      seqs[i] = -1;
      break;
    }

  if (i==NR_TIMERS) printf("stop_timer %u ARG\n", seq);
  recalc_timers();		/* figure out which timer is now lowest */
}

void start_ack_timer(void)
{
/* Start the auxiliary timer for sending separate acks. The length of the
 * auxiliary timer is arbitrarily set to half the main timer.  This could
 * have been another simulation parameter, but that is unlikely to have
 * provided much extra insight.
 */

  aux_timer = tick + timeout_interval/AUX;
  offset++;
}

void stop_ack_timer(void)
{
/* Stop the ack timer. */

  aux_timer = 0;
}

void dump_timers(void)
{
  int i, min, imin;
  int l = lowest_timer;

  printf("timers: ");
  for (i=0; i < NR_TIMERS; i++)
    if (ack_timer[i] == l) break;
  if (i==NR_TIMERS) return;
  printf("%u:%u(%u) ", seqs[i], i, ack_timer[i]);

  while (1) {
    min = 99999;
    imin = -1;
    for (i=0; i < NR_TIMERS; i++)
      if (ack_timer[i] < min && ack_timer[i] > l) {
	min = ack_timer[i];
	imin = i;
      }
    if (imin==-1) break;
    printf("%u:%u(%u) ", seqs[imin], imin, ack_timer[imin]);
    l = min;
  }
}

int check_timers(void)
{
/* Check for possible timeout.  If found, reset the timer. */

  int i;

  /* See if a timeout event is even possible now. */
  if (lowest_timer == 0 || tick < lowest_timer) return(-1);

  /* A timeout event is possible.  Find the lowest timer. Note that it is
   * impossible for two frame timers to have the same value, so that when a
   * hit is found, it is the only possibility.  The use of the offset variable
   * guarantees that each successive timer set gets a higher value than the
   * previous one.
   */
  for (i = 0; i < NR_TIMERS; i++) {
	if (ack_timer[i] == lowest_timer) {
		ack_timer[i] = 0;	/* turn the timer off */
		recalc_timers();	/* find new lowest timer */
                timedout_seq = seqs[i];	/* timed out sequence number */
		timedout_buf = i;
		return(i);
	}
  }
  printf("Impossible.  check_timers failed at %lu\n", lowest_timer);
  exit(1);
}


int check_ack_timer()
{
/* See if the ack timer has expired. */

  if (aux_timer > 0 && tick >= aux_timer) {
	aux_timer = 0;
	return(1);
  } else {
	return(0);
  }
}

void recalc_timers(void)
{
/* Find the lowest timer */

  int i;
  bigint t = UINT_MAX;

  for (i = 0; i < NR_TIMERS; i++) {
	if (ack_timer[i] > 0 && ack_timer[i] < t) t = ack_timer[i];
  }
  lowest_timer = t;
}



/* ---- network layer */

void from_network_layer(packet *p)
{
/* Fetch a packet from the network layer for transmission on the channel. */

  p->data[0] = (next_net_pkt >> 24) & BYTE;
  p->data[1] = (next_net_pkt >> 16) & BYTE;
  p->data[2] = (next_net_pkt >>  8) & BYTE;
  p->data[3] = (next_net_pkt      ) & BYTE;
  next_net_pkt++;
}


void to_network_layer(packet *p)
{
/* Deliver information from an inbound frame to the network layer. A check is
 * made to see if the packet is in sequence.  If it is not, the simulation
 * is terminated with a "protocol error" message.
 */

  unsigned int num;

  num = pktnum(p);
  if (num != last_pkt_given + 1) {
	printf("Tick %lu. Protocol failure detected on %c."
	       "  Packet delivered out of order.\n", tick/DELTA, id?'B':'A'); 
	printf("Expected payload %d but got payload %d\n",last_pkt_given+1,num);
	exit(0);
  }
  last_pkt_given = num;
  payloads_accepted++;
}


void enable_network_layer(void)
{
/* Allow network_layer_ready events to occur. */

  network_layer_status = 1;
}


void disable_network_layer(void)
{
/* Prevent network_layer_ready events from occuring. */

  network_layer_status = 0;
}

uint_t pktnum(packet *p)
{
/* Extract packet number from packet. */

  unsigned int num, b0, b1, b2, b3;

  b0 = p->data[0] & BYTE;
  b1 = p->data[1] & BYTE;
  b2 = p->data[2] & BYTE;
  b3 = p->data[3] & BYTE;
  num = (b0 << 24) | (b1 << 16) | (b2 << 8) | b3;
  return(num);
}


void print_statistics(void)
{
/* Display statistics. */

  int word[3];

  printf("\nProcess %c:\n", id?'B':'A');
  printf("\tTotal data frames sent:  %9d\n", data_sent);
  printf("\tData frames lost:        %9d\n", data_lost);
  printf("\tData frames not lost:    %9d\n", data_not_lost);
  printf("\tFrames retransmitted:    %9d\n", data_retransmitted);
  printf("\tGood ack frames rec'd:   %9d\n", good_acks_recd);
  printf("\tBad ack frames rec'd:    %9d\n\n", cksum_acks_recd);

  printf("\tGood data frames rec'd:  %9d\n", good_data_recd);
  printf("\tBad data frames rec'd:   %9d\n", cksum_data_recd);
  printf("\tPayloads accepted:       %9d\n", payloads_accepted);
  printf("\tTotal ack frames sent:   %9d\n", acks_sent);
  printf("\tAck frames lost:         %9d\n", acks_lost);
  printf("\tAck frames not lost:     %9d\n", acks_not_lost);

  printf("\tTimeouts:                %9d\n", timeouts);
  printf("\tAck timeouts:            %9d\n", ack_timeouts);
  fflush(stdin);

  word[0] = 0;
  word[1] = payloads_accepted;
  word[2] = data_sent;
  write(mwfd, word, 3*sizeof(int));	/* tell main we are done printing */
  exit(0);
}
