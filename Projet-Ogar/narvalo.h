#include "libwebsockets.h"

#define NBCELLMAX 16
#define SPLITPOSSIBLEMASS 37

#define SPLITVIRUSMASS 130

#define ENVIRODESERT 50

#define SUPAFAT 1500
#define ALONELIMIT 100





// ************************** POUR LE CLIENT.C **************************************

// RECEIVE_FONCTION
void receive_fonction (unsigned char *rbuf, int len, struct lws * wsi);
int distance(int pos_bot_x,int pos_food_x, int pos_bot_y,int pos_food_y);
void make_struct_pos (int xpos,int ypos);
int cursor_pos_x;
int cursor_pos_y;
int food_pos_x;
int food_pos_y;
// UPDATE NODE MESSAGE
int position_pointeur;


typedef struct __attribute__((__packed__)) node {
        unsigned int Id;
        int x;
        int y;
        unsigned short size;
        unsigned char flag;
        unsigned char R,G,B;
        char* name;
} node;


typedef struct __attribute__((__packed__)) liste {
        node* node;
        struct liste* next;
} liste ;


// BORDER INFORMATION MESSAGE-----------------------------------------------------

typedef struct border_screen {
  double * bord_L;
  double * bord_R;
  double * bord_B;
  double * bord_T;
  int X1;
  int Y1;
  int X2;
  int Y2;
  } screen;

// ADD NODE MESSAGE -----------------------------------------------------------

// POUR LE DEPLACEMENT --------------------------------------------------------

typedef struct __attribute__((__packed__)) pos_curseur {
  int x_pos;
  int y_pos;
}pos_curseur;


pos_curseur* get_pos();
// compter_nos_morts -----------------------------------------------------------
void compter_nos_morts (unsigned char * paquet, int offset);


// ************************** POUR LE NARVALO.C **************************************
int id_petite();

void fonction_40 (unsigned char * rbuf);
void fonction_20 (unsigned char * rbuf);
void fonction_10 (unsigned char * rbuf);
unsigned char * return_nickname ();
unsigned char * return_split ();

int return_dead ();

void sendSplit (struct lws *wsi);

int dense_virus ();

int calcul_masse ();

void beaucoup_trop ();

int nb_food_screen ();

void compter_adversaires ();

void force_exit ();


int contact_virus ();

int id_max();
