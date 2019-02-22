/* Simulator for datalink protocols. 
 *    Written by Andrew S. Tanenbaum.
 *    Revised by Shivakant Mishra.
 *    Revised by Christophe Deleuze.
 */

#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "simulator.h"

#define DEADLOCK (3 * timeout_interval)	/* defines what a deadlock is */
#define MANY 256		/* big enough to clear pipe at the end */

bigint tick = 0;		/* the current time, measured in events */
bigint last_tick;		/* when to stop the simulation */
int exited[2];			/* set if exited (for each worker) */
int hanging[2];			/* # times a process has done nothing */
struct sigaction act, oact;

/* Prototypes. */
void start_simulator(void (*p1)(), void (*p2)(), long event, int tm_out, int pk_loss, int grb, int d_flags);
void set_up_pipes(void);
void fork_off_workers(void);
void terminate(char *s);

void sim_error(char *s);
int parse_first_five_parameters(int argc, char *argv[], long *event, int *timeout_interval, int *pkt_loss, int *garbled, int *debug_flags);


void start_simulator(void (*p1)(int), void (*p2)(int), long event,
		     int tm_out, int pk_loss, int grb, int d_flags)
{
/* The simulator has three processes: main(this process), A, and B, all of
 * which run independently.  Set them all up first.  Once set up, main
 * maintains the clock (tick), and picks a process to run.  Then it writes a
 * 32-bit word to that process to tell it to run.  The process sends back an
 * answer when it is done.  Main then picks another process, and the cycle
 * repeats.
 */

  int process = 0;		/* whose turn is it */
  int rfd, wfd;			/* file descriptor for talking to workers */
  bigint word;			/* message from worker */

  act.sa_handler = SIG_IGN;
  //setvbuf(stdout, (char *) 0, _IONBF, (size_t) 0);	/* disable buffering*/

  proc1 = p1;
  proc2 = p2;
  /* Each event uses DELTA ticks to make it possible for each timeout to
   * occur at a different tick.  For example, with DELTA = 10, ticks will
   * occur at 0, 10, 20, etc.  This makes it possible to schedule multiple
   * events (e.g. in protocol 5), all at unique times, e.g. 1070, 1071, 1072,
   * 1073, etc.  This property is needed to make sure timers go off in the
   * order they were set.  As a consequence, internally, the variable tick
   * is bumped by DELTA on each event. Thus asking for a simulation run of
   * 1000 events will give 1000 events, but they internally they will be
   * called 0 to 10,000.
   */
  last_tick = DELTA * event; 

  /* Convert from external units to internal units so the user does not see
   * the internal units at all.
   */
  timeout_interval = DELTA * tm_out;

  /* Packet loss takes place at the sender.  Packets selected for being lost
   * are not put on the wire at all.  Internally, pkt_loss and garbled are
   * from 0 to 990 so they can be compared to 10 bit random numbers.  The
   * inaccuracy here is about 2.4% because 1000 != 1024.  In effect, it is
   * not possible to say that all packets are lost.  The most that can be
   * be lost is 990/1024.
   */

  pkt_loss = 10 * pk_loss; /* for our purposes, 1000 == 1024 */

  /* This arg tells what fraction of arriving packets are garbled.  Thus if
   * pkt_loss is 50 and garbled is 50, half of all packets (actually,
   * 500/1024 of all packets) will not be sent at all, and of the ones that
   * are sent, 500/1024 will arrive garbled.
   */

  garbled = 10 * grb; /* for our purposes, 1000 == 1024 */

  /* Turn tracing options on or off.  The bits are defined in worker.c. */
  debug_flags = d_flags;
  printf("\n\nEvents: %lu    Parameters: %lu %d %u\n",
      last_tick/DELTA, timeout_interval/DELTA, pkt_loss/10, garbled/10);

  if (debug_flags) printf("\n\t\t          A     \t           B\n");
  if (debug_flags) printf("\t\t      --------- \t       ----------\n\n");

  fflush(stdout);
  set_up_pipes();		/* create five pipes */
  fork_off_workers();		/* fork off the worker processes */



/*   /\* Main simulation loop. *\/ */
/*   while (tick <last_tick) { */
/*     //process = (process?0:1); */
/*     process = rand() & 1;		/\* pick process to run: 0 or 1 *\/ */
/*     //    if (process) */
/* 	tick = tick + DELTA; */
/* 	rfd = (process == 0 ? r4 : r6); */
/* 	if (read(rfd, &word, TICK_SIZE) != TICK_SIZE) terminate(""); */
/* 	if (word == OK) hanging[process] = 0; */
/* 	if (word == NOTHING) hanging[process] += DELTA; */
/* 	if (hanging[0] >= DEADLOCK && hanging[1] >= DEADLOCK) */
/* 		terminate("A deadlock has been detected"); */

/* 	/\* Write the time to the selected process to tell it to run. *\/ */
/* 	wfd = (process == 0 ? w3 : w5); */
/* 	if (write(wfd, &tick, TICK_SIZE) != TICK_SIZE) */
/* 		terminate("Main could not write to worker"); */
/*   } */

  if (read(r4, &word, TICK_SIZE) != TICK_SIZE) terminate("");
  if (read(r6, &word, TICK_SIZE) != TICK_SIZE) terminate("");

  while (tick<last_tick) {
    tick += DELTA;

    /* ZZZ choisir l'ordre de manière aléatoire ? */

    for (process=0; process<2; process++) {
      wfd = process ? w5 : w3;
      rfd = process ? r6 : r4;
      write(wfd, &tick, TICK_SIZE);
      if (read(rfd, &word, TICK_SIZE) != TICK_SIZE) terminate("");
      if (word == OK) hanging[process] = 0; 
      if (word == NOTHING) hanging[process] += DELTA;
      if (hanging[0] >= DEADLOCK && hanging[1] >= DEADLOCK)
	terminate("A deadlock has been detected");
    }
  }
    
  /* Simulation run has finished. */
  terminate("End of simulation");
}


void set_up_pipes(void)
{
/* Create six pipes so main, A and B can communicate pairwise. */

  int fd[2];

  pipe(fd);  r1 = fd[0];  w1 = fd[1];	/* A to B for frames */
  pipe(fd);  r2 = fd[0];  w2 = fd[1];	/* B to A for frames */
  pipe(fd);  r3 = fd[0];  w3 = fd[1];	/* main to A for go-ahead */
  pipe(fd);  r4 = fd[0];  w4 = fd[1];	/* A to main to signal readiness */
  pipe(fd);  r5 = fd[0];  w5 = fd[1];	/* main to B for go-ahead */
  pipe(fd);  r6 = fd[0];  w6 = fd[1];	/* B to main to signal readiness */
}

void fork_off_workers(void)
{
/* Fork off the two workers, A and B. */

  if (fork() != 0) {
	/* This is the Parent.  It will become main, but first fork off B. */
	if (fork() != 0) {
		/* This is main. */
		sigaction(SIGPIPE, &act, &oact);
	        setvbuf(stdout, (char *)0, _IONBF, (size_t)0);/*don't buffer*/
		close(r1);
		close(w1);
		close(r2);
		close(w2);
		close(r3);
		close(w4);
		close(r5);
		close(w6);
		return;
	} else {
		/* This is the code for B. Run protocol. */
		sigaction(SIGPIPE, &act, &oact);
	        setvbuf(stdout, (char *)0, _IONBF, (size_t)0);/*don't buffer*/
		close(w1);
		close(r2);
		close(r3);
		close(w3);
		close(r4);
		close(w4);
		close(w5);
		close(r6);
	
		id = 1;		/* B gets id 1 */
		mrfd = r5;	/* fd for reading time from main */
		mwfd = w6;	/* fd for writing reply to main */
		prfd = r1;	/* fd for reading frames from worker 0 */
		(*proc2)(1);	/* call the user-defined protocol function */
		terminate("Impossible.  Protocol terminated");
	}
  } else {
	/* This is the code for A. Run protocol. */
	sigaction(SIGPIPE, &act, &oact);
        setvbuf(stdout, (char *)0, _IONBF, (size_t)0);/*don't buffer*/
	close(r1);
	close(w2);
	close(w3);
	close(r4);
	close(r5);
	close(w5);
	close(r6);

	id = 0;		/* A gets id 0 */
	mrfd = r3;	/* fd for reading time from main */
	mwfd = w4;	/* fd for writing reply to main */
	prfd = r2;	/* fd for reading frames from worker 1 */
	(*proc1)(0);	/* call the user-defined protocol function */
	terminate("Impossible. protocol terminated");
  }
}

void terminate(char *s)
{
/* End the simulation run by sending each worker a 32-bit zero command. */

  int n, k1, k2, res1[MANY], res2[MANY], eff, acc, sent;

  for (n = 0; n < MANY; n++) {res1[n] = 0; res2[n] = 0;}

  /* Clean out the pipe.  The zero word indicates start of statistics. */
  write(w3, &zero, TICK_SIZE);
  read(r4, res1, MANY*sizeof(int));
  k1 = 0;
  while (res1[k1] != 0) k1++;
  k1++;				/* res1[k1] = accepted, res1[k1+1] = sent */

  write(w5, &zero, TICK_SIZE);
  /* Clean out the other pipe and look for statistics. */
  read(r6, res2, MANY*sizeof(int));
  k2 = 0;
  while (res2[k2] != 0) k2++;
  k2++;				/* res1[k2] = accepted, res1[k2+1] = sent */

  if (strlen(s) > 0) {
    acc = res1[k1] + res2[k2];
    sent = res1[k1+1] + res2[k2+1];
    if (sent > 0) {
      eff = (100 * acc)/sent;
      printf("\nEfficiency (payloads accepted/data pkts sent) = %d%c\n", eff, '%');
    }
    printf("%s.  Time=%lu\n",s, tick/DELTA);
  }
  exit(eff);
}

/* ---- .... */

void sim_error(char *s)
{
/* A simulator error has occurred. */

  int fd;

  printf("%s\n", s);
  fd = (id == 0 ? w4 : w6);
  write(fd, &zero, TICK_SIZE);
  exit(-1);
}

int parse_first_five_parameters(int argc, char *argv[], long *event, int *timeout_interval, int *pkt_loss, int *garbled, int *debug_flags)
{
/* Help function for protocol writers to parse first five command-line
 * parameters that the simulator needs.
 */

  if (argc < 5) {
        printf("Need at least five command-line parameters.\n");
        return(0);
  }
  *event = atol(argv[1]);
  if (*event < 0) {
        printf("Number of simulation events must be positive\n");
        return(0);
  }
  *timeout_interval = 50;
  /*  *timeout_interval = atoi(argv[2]);
  if (*timeout_interval < 0){
        printf("Timeout interval must be positive\n");
        return(0);
	}*/
  *pkt_loss = atoi(argv[2]);     /* percent of sends that chuck pkt out */
  if (*pkt_loss < 0 || *pkt_loss > 99) {
        printf("Packet loss rate must be between 0 and 99\n");
        return(0);
  }
  *garbled = atoi(argv[3]);
  if (*garbled < 0 || *garbled > 99) {
        printf("Packet cksum rate must be between 0 and 99\n");
        return(0);
  }
  *debug_flags = atoi(argv[4]);
  if (*debug_flags < 0) {
        printf("Debug flags may not be negative\n");
        return(0);
  }
  duplex = atoi(argv[5]);
  return(1);
}
