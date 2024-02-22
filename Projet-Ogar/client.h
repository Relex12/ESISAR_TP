#include "libwebsockets.h"
#define MAXLEN 20000

static int callbackOgar(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len);

int forceExit;

typedef struct s_packet {
        unsigned char buf[MAXLEN+LWS_PRE];
        unsigned int len;
        struct s_packet *next;
} t_packet;

/// Pointer on the list of packet to be send when socket is writeable
t_packet *packetList=NULL;

/// LibWebsocket interlan structure needed for API
struct lws_protocols protocols[] = {
    {
        "ogar_protocol",
    callbackOgar,
        0,
        20
        },
    {
    NULL,
    NULL,
    0,
    0
    }
};
