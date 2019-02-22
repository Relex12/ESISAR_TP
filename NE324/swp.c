/* swp - simple sliding window protocol */

#include <stdlib.h>
#include <stdio.h>

#define NSEQ 8

#define SWS 4
#define RWS 4

#include "protocol.h"

#define start_timer(s) start_timer(s,s)


#define inc_seq(k)  k = (k + 1) % NSEQ
#define pred_seq(s) (s==0?NSEQ-1:s-1)

/* is seq number s in [a, b[ ? */
static bool seq_between(uint_t s, uint_t a, uint_t b)
{
  return ((a<=s) && (s<b)) || ((b<a) && (a<=s)) || ((b<a) && (s<b));
}

#define is_new_ack(s,sw1,sw2)    seq_between(pred_seq(s), sw1, sw2)
#define in_rcv_window(s,rw1,RWS) seq_between(s, rw1, (rw1+RWS) % NSEQ)


static void send_data_frame(uint_t seq, uint_t ack, packet *buf)
{
  frame s;

  s.kind = data;
  s.info = buf[seq];
  s.seq = seq;
  s.ack = ack;

  /* transmit the frame */
  to_physical_layer(&s);

  start_timer(seq);
  stop_ack_timer();	/* since we just sent a piggybacked ack */
}

static void send_ack_frame(uint_t seq)
{
  frame s;

  s.kind = ack;
  s.ack  = seq;

  /* transmit the frame */
  to_physical_layer(&s);
  stop_ack_timer();	/* since we just sent one */
}

static void send_nak_frame(uint_t seq)
{
  frame s;

  s.kind = nak;
  s.ack  = seq;

  /* transmit the frame */
  to_physical_layer(&s);
  stop_ack_timer();	/* since we just sent one */
}

void swp(int id)
{
  uint_t sw1 = 0;           /* first non acked frame*/
  uint_t sw2 = 0;           /* next frame to send */
  packet snd_buf[NSEQ];     /* sending buffers */
  uint_t nbuffered = 0;     /* how many are currently used */

  uint_t rw1 = 0;           /* expected frame  */
  packet rcv_buf[NSEQ];     /* receive buffers */
  bool   arrived[NSEQ];     /* which are used  */

  int i;
  frame r;
  event_type event;

  enable_network_layer();
  for (i = 0; i < NSEQ; i++) arrived[i] = false;

  while (true) {


    wait_for_event(&event);

    switch(event) {

    case network_layer_ready:   /* accept, save, and transmit a new frame */
      nbuffered++;

      /* fetch new packet */
      from_network_layer(&snd_buf[sw2]);

      /* transmit the frame */
      send_data_frame(sw2, rw1, snd_buf);
      inc_seq(sw2);
      break;

    case frame_arrival:            /* a data or control frame has arrived */
      from_physical_layer(&r);

	 if (r.kind == nak && seq_between(r.ack,sw1,sw2)) {
		  send_data_frame(r.ack, rw1, snd_buf);

	  } else
	 {

      /* data frame */
      if (r.kind == data) {
	/* to see if a separate ack is needed */
	start_ack_timer();

	if (in_rcv_window(r.seq, rw1, RWS) && (arrived[r.seq] == false)) {

	  /* this is a new frame */
	  arrived[r.seq] = true;
	  rcv_buf[r.seq] = r.info;

	  while (arrived[rw1] == true) {
	    /* Pass frames and slide receiver's window. */
	    to_network_layer(&rcv_buf[rw1]);
	    arrived[rw1] = false;
	    inc_seq(rw1);
	  }
	}
      }
  }

      /* handle ACK */
      while (is_new_ack(r.ack, sw1, sw2)) {
	nbuffered = nbuffered - 1;
	stop_timer(sw1);
	inc_seq(sw1);    /* advance sender's window */
      }
      break;

    case cksum_err:    /* damaged frame */
	if (r.kind == data) {
		send_ack_frame(rw1);
		send_nak_frame(rw1);
	}

      break;

    case timeout:    /* no ack arrived */
      send_data_frame(get_timedout_seqnr(), rw1, snd_buf);
      break;

    case ack_timeout:   /* ack timer expired; send ack */
      send_ack_frame(rw1); break;
    }

    /* check wether sending window is full */
    if (nbuffered < SWS) enable_network_layer();
    else disable_network_layer();
  }
}

int main (int argc, char *argv[])
{
  int timeout_interval, pkt_loss, garbled, debug_flags;
  long event;

  if (!parse_first_five_parameters(argc, argv, &event, &timeout_interval,
                                   &pkt_loss, &garbled, &debug_flags)) {
    printf ("Usage: swp events loss cksum debug duplex\n");
    exit(1);
  }

  printf("\n\n Simulating Protocol SWP\n");
  srand(0);
  start_simulator(swp, swp, event, timeout_interval,
		  pkt_loss, garbled, debug_flags);
  return 0;
}
