#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <signal.h>
#include <syslog.h>
#include <sys/time.h>
#include <unistd.h>

#include "client.h"
#include "narvalo.h"

unsigned char cursor_pos [13] = {0x10,0,0,0,0,0,0,0,0,0,0,0,0};

// COMPILATION : gcc -Wall -g -o sock ./test-client.c -lwebsockets


// =====================================================================================================================================
//    Start of function definition
// =====================================================================================================================================

// Caught on CTRL C
void sighandler(int sig)
{
    forceExit = 1;
}


/**
\brief Allocate a packet structure and initialise it.
\param none
\return pointer to new allocated packet
****************************************************************************************************************************/
t_packet *allocatePacket()
{
    t_packet *tmp;

    if ((tmp=malloc(sizeof(t_packet))) == NULL ) return NULL;
    memset(tmp,0,sizeof(t_packet));
    return tmp;
}

/**
\brief Add a packet to the list of packet to be sent
\param wsi websocket descriptor
\param buf buffer to be sent
\param len length of packet
\return pointer to new allocated packet

// FONCTION SEND COMMAND  ****************************************************************************************************************************/

int sendCommand(struct lws *wsi,unsigned char *buf,unsigned int len)
{
    t_packet *tmp,*list=packetList;

    if (len > MAXLEN ) return -1;
    if ((tmp=allocatePacket()) == NULL ) return -1;
    memcpy(&(tmp->buf)[LWS_PRE],buf,len);
    tmp->len=len;
    if (packetList == NULL )
        packetList=tmp;
    else {
        while (list && list->next) {
            list=list->next;
        }
        list->next=tmp;
    }
    lws_callback_on_writable(wsi);
    return 1;
}

/****************************************************************************************************************************/


int writePacket(struct lws *wsi)
{
    t_packet *tmp=packetList;
    int ret;

    if (packetList == NULL ) return 0;

    packetList=tmp->next;
    ret=lws_write(wsi,&(tmp->buf)[LWS_PRE],tmp->len,LWS_WRITE_BINARY);
    free(tmp);
    lws_callback_on_writable(wsi);
    return(ret);
}

// *************************** FONCTIONS AJOUTEES ***************************************
// SEND SPLIT -------------------------------------------------------------------
void sendSplit (struct lws *wsi)
{
    if (NULL != return_split())
  {
    sendCommand(wsi, return_split(), 2);
  }
}

// RECEIVE FONCTION -------------------------------------------------------------------

void receive_fonction (unsigned char *rbuf, int len, struct lws *wsi)
{
    memcpy(cursor_pos+1, get_pos(), sizeof(pos_curseur));
    sendCommand (wsi, cursor_pos, 13);
  sendSplit (wsi);

    switch (rbuf[0]) {
        case 0x12: // Nickname
            sendCommand (wsi, return_nickname(), 9);            // si le nickname est modifié, la valeur 9 mènera à une erreur
            break;
    case 0x40:    // Border Information Message
            fonction_40(rbuf);
            break;
    case 0x20:    // Add Node Message
            fonction_20 (rbuf);
        break;
        case 0x10:    // Update Node Message
            compter_nos_morts (rbuf, len);
            fonction_10 (rbuf);
            break;
        default:    // Cas par défaut
            break;
    }
    if (return_dead() != 0)
    {
        forceExit = 1;
        fprintf(stderr, "C'est le décès pour Narvalo\n");
    }
    force_exit();
}

void force_exit ()
{
    if (forceExit == 1)
        fprintf(stderr, "Le meilleur score de Narvalo était de : %d\n", return_dead());
}


/*
sendCommand (wsi, return_split(), 9);
sendCommand (wsi, return_cursor(), 9);

*/

// *************************** FONCTION CALLBACKOGAR ***************************************
static int callbackOgar(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
{
    static unsigned int offset=0;
    static unsigned char rbuf[MAXLEN];

    switch (reason) {
    case LWS_CALLBACK_CLIENT_ESTABLISHED:
        fprintf(stderr, "ogar: LWS_CALLBACK_CLIENT_ESTABLISHED\n");
        unsigned char connexion_start_command [] = {0xff,0x00,0x00,0x00,0x00};
        unsigned char connexion_command [] = {0xfe,0x0d,0x00,0x00,0x00};
        sendCommand (wsi ,connexion_start_command,5);        // requête de connexion
        sendCommand (wsi ,connexion_command,5);                    // connexion avec le serveur

        break;

     case LWS_CALLBACK_CLIENT_WRITEABLE:
        if (writePacket(wsi) < 0 ) forceExit=1;
        break;

    case LWS_CALLBACK_CLIENT_RECEIVE:
        // we have receive some data, check if it can be written in static allocated buffer (length)

        if (offset + len < MAXLEN ) {
            memcpy(rbuf+offset,in,len);
            offset+=len;
            // we have receive some data, check with websocket API if this is a final fragment
            if (lws_is_final_fragment(wsi)) {
                receive_fonction (rbuf, len, wsi);                // APPEL DE NOTRE FONCTION RECEIVE_FONCTION
                offset=0;
            }
        } else {    // length is too long... get others but ignore them...
            offset=MAXLEN;
             if ( lws_is_final_fragment(wsi) ) {
                offset=0;
            }
        }
        break;
    case LWS_CALLBACK_CLOSED:
        lwsl_notice("ogar: LWS_CALLBACK_CLOSED\n");
        forceExit = 1;
        break;
    case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
        lwsl_err("ogar: LWS_CALLBACK_CLIENT_CONNECTION_ERROR\n");
        forceExit = 1;
        break;

    case LWS_CALLBACK_COMPLETED_CLIENT_HTTP:
        lwsl_err("ogar: LWS_CALLBACK_COMPLETED_CLIENT_HTTP\n");
        forceExit = 1;
        break;

    default:
        break;
    }

    return 0;
}


// **************************************** MAIN ********************************************************************
int main(int argc, char **argv)
{
    int n = 0;

    struct lws_context_creation_info info;
    struct lws_client_connect_info i;

    struct lws_context *context;
    const char *protocol,*temp;

    memset(&info, 0, sizeof info);
    memset(&i, 0, sizeof(i));

    if (argc < 2)
        goto usage;

    while (n >= 0) {
        n = getopt(argc, argv, "hsp:P:o:");
        if (n < 0)
            continue;
        switch (n) {
        case 's':
            i.ssl_connection = 2;
            break;
        case 'p':
            i.port = atoi(optarg);
            break;
        case 'o':
            i.origin = optarg;
            break;
        case 'P':
            info.http_proxy_address = optarg;
            break;
        case 'h':
            goto usage;
        }
    }

    srandom(time(NULL));

    if (optind >= argc)
        goto usage;

    signal(SIGINT, sighandler);

    if (lws_parse_uri(argv[optind], &protocol, &i.address, &i.port, &temp))
        goto usage;

    if (!strcmp(protocol, "http") || !strcmp(protocol, "ws"))
        i.ssl_connection = 0;
    if (!strcmp(protocol, "https") || !strcmp(protocol, "wss"))
        i.ssl_connection = 1;

    i.host = i.address;
    i.ietf_version_or_minus_one = -1;
    i.client_exts = NULL;
    i.path="/";

    info.port = CONTEXT_PORT_NO_LISTEN;
    info.protocols = protocols;
    info.gid = -1;
    info.uid = -1;

    context = lws_create_context(&info);
    if (context == NULL) {
        fprintf(stderr, "Creating libwebsocket context failed\n");
        return 1;
    }

    i.context = context;

    if (lws_client_connect_via_info(&i)); // just to prevent warning !!

    forceExit=0;
    // the main magic here !!
    while (!forceExit) {
        lws_service(context, 1000);
    }
    // if there is some errors, we just quit
    lwsl_err("Exiting\n");
    lws_context_destroy(context);

    return 0;

usage:
    fprintf(stderr, "Usage: ogar-client -h -s -p <port> -P <proxy> -o <origin>  <server address> \n");
    return 1;
}



