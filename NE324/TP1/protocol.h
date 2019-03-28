#define MAX_PKT 4	/* determines packet size in bytes */

typedef unsigned int buf_t;

typedef enum {false, true} bool;	/* boolean type */
typedef unsigned int uint_t;	/* sequence or ack numbers */
typedef struct {unsigned char data[MAX_PKT];} packet;	/* packet definition */
typedef enum {data, ack, nak} frame_kind;	/* frame_kind definition */

typedef enum {frame_arrival, cksum_err,
	      timeout, network_layer_ready, ack_timeout} event_type;

typedef struct {	/* frames are transported in this layer */
  frame_kind kind;	/* what kind of a frame is it? */
  uint_t seq;   	/* sequence number */
  uint_t ack;   	/* acknowledgement number */
  packet info;  	/* the network layer packet */
} frame;

/* start_simulator initializes various simulator parameters and starts the
 * simulation. Control will return from this function only after the simulation
 * has been completed. 
 *
 * Parameter description:
 *   proc1: function name of the protocol function that is executed by one
 *          end of the link.
 *   proc2: function name of the protocol function that is executed by the
 *          other end of the link. For several datalink protocols, proc1 and
 *          proc2 may be same, e.g. protocols 4, 5, and 6.
 *   event: how long (in terms of number of events) the simulation should run.
 *   tm_out: timeout interval in ticks.
 *   pk_loss: percentage of frames that are lost (0-99).
 *   grb: percentage of arriving frames that are bad (due to checksum errors).
 *   d_flags: enables various tracing flags.
 *              1        frames sent
 *              2        frames received
 *              4        timeouts
 *              8        periodic printout for use with long runs
 */
void start_simulator(void (*proc1)(), void (*proc2)(), long event,
                     int tm_out, int pk_loss, int grb, int d_flags);

/* Wait for an event to happen; return its type in event. */
void wait_for_event(event_type *event);

/* Fetch a packet from the network layer for transmission on the channel. */
void from_network_layer(packet *p);

/* Deliver information from an inbound frame to the network layer. */
void to_network_layer(packet *p);

/* Go get an inbound frame from the physical layer and copy it to r. */
void from_physical_layer(frame *r);

/* Pass the frame to the physical layer for transmission. */
void to_physical_layer(frame *s);

/* Start the clock running and enable the timeout event. */
void start_timer(uint_t seq, uint_t buf);

/* Stop the clock and disable the timeout event. */
void stop_timer(uint_t seq);

/* After a timeout occured, get seq nb and buffer */
uint_t get_timedout_seqnr(void);
uint_t get_timedout_buf(void);

/* Start an auxiliary timer and enable the ack_timeout event. */
void start_ack_timer(void);

/* Stop the auxiliary timer and disable the ack_timeout event. */
void stop_ack_timer(void);

/* Allow the network layer to cause a network_layer_ready event. */
void enable_network_layer(void);

/* Forbid the network layer from causing a network_layer_ready event. */
void disable_network_layer(void);


/* Help function for protocol designers to parse first five command-line
 * parameters that the simulator needs. This assumes that the first five
 * command-line parameters are the simulator parameters. If a protocol needs
 * any additional parameters, it needs to parse them separately.
 */
int parse_first_five_parameters(int argc, char *argv[], long *event,
                                int *timeout_interval, int *pkt_loss,
                                int *garbled, int *debug_flags);
