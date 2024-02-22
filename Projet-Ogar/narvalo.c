#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <signal.h>
#include <syslog.h>
#include <sys/time.h>
#include <unistd.h>
#include <math.h>

#include "narvalo.h"

// VARIABLES ET POINTEURS, ASSIGNATION -----------------------------------------------------------------------------------

int i;
int nbcellnotoexceed = 0;       // en fonction du mode de jeu parmi solo, duel ou battle royale
int split_attaque;              // variable qui permet de savoir si il faut split pour pouvoir manger un autre joueur
char attaque_accomplie;         // sert à attaquer un ennemi grâce au split
int virus_no=0;                 // variable qui permet de configurer notre bot afin qu'il ne mange plus de virus
int score_max = 0;              // contient le score maximal du bot
char game_mode = 0x01;          // 0x01 pour le solo, 0x02 pour le duel ou le battle royale
int x_bot_pos_max;
int y_bot_pos_max;
int cursor_bot_x;
int cursor_bot_y;

// Update Node
liste * node_before_info = NULL;
liste * node_new_info = NULL;
pos_curseur Pos;
int x_bot_pos;                    // donne la position de notre bot sur la coordonnée X
int y_bot_pos;                    // donne la position de notre bot sur la coordonnée Y
int id_du_bot;                    // cette variable sert a récupérer l'id de notre bot (soit le plus gros, soit le plus petit)
int split_urgence = 0;            // sert a faire split notre bot lorsqu'il est en grand danger

// Border Information
screen map;
screen player;
screen * game;
int map_q = 0;                    // map_q = 0 si le paquet traîté est le premier 0x40 reçu

// Add Node
int idents[NBCELLMAX];    // tableau contenant les identifants de toutes les cellules nous appartenant
int nb_ids = 0;           // contient le nombre de nos cellules
int temp_id;              // sert à ajouter des identifiants dans le tableau

// compter_nos_morts
int nb_morts;             // contient le nombre de cellules mortes pour chaque Update Node Message
int * p_killed;           // pointeur pointant vers une cellule morte pour savoir si elle nous appartient
int killed_temp;          // prend l'ID de la cellule morte
int j;

// dense_virus
int virus_present = 0;    // sert à déterminer si la carte est vide de tout virus

// return_nickname
unsigned char nickname[9] = "\0Narvalo";    // nom de nos cellules

// return_split
unsigned char split = 0x11;     // pour split, un pointeur pointera vers cette variable constante

// return_cursor
unsigned char *position_cursor;


// FONCTIONS *****************************************************************************************************************
// Fonction distance ------------------------------------------------------------------------------------------------------------
int distance(int pos_bot_x,int pos_food_x, int pos_bot_y,int pos_food_y)
{
  return sqrt( pow((pos_bot_x - pos_food_x), 2) + pow((pos_bot_y - pos_food_y),2) );
}

// Fonction pour la pos du pos du curseur
void make_struct_pos (int xpos,int ypos)
{
  Pos.y_pos = ypos;
  Pos.x_pos = xpos;
}

// Fonction Get Pos
pos_curseur* get_pos()
{
  return &Pos;
}

// SI RECU LE PAQUET BORDER INFOMARTION *********************************************************************************
void fonction_40 (unsigned char * rbuf)
{
  i = 1;
  if (map_q == 0)                    // si c'est le premier message Border Information
  {
      game = & map;                    // game pointe vers map
      map_q++;
  }
  else
  {
    game = & player;            // sinon game pointe vers player
  }

  game->bord_L = (double *) &(rbuf[i]);            // les bordures sont codées sur 8 octets, ce sont des doubles
  game->X1 = (int) *(game->bord_L);                    // le bord d'écran de gauche est stocké dans player.bord_L
  i = i + 8;                                                                // on passe à la bordure suivante
  game->bord_T = (double *) &(rbuf[i]);            // on recommence avec la bordure suivante
  game->Y1 = (int) *(game->bord_T);
  i = i + 8;
  game->bord_R = (double *) &(rbuf[i]);
  game->X2 = (int) *(game->bord_R);
  i = i + 8;
  game->bord_B = (double *) &(rbuf[i]);
  game->Y2 = (int) *(game->bord_B);
  i = 0;
}


// SI RECU LE PAQUET ADD NODE *********************************************************************************
void fonction_20 (unsigned char * rbuf)
{
  temp_id = rbuf[1] + (NBCELLMAX*NBCELLMAX)*rbuf[2] + (NBCELLMAX*NBCELLMAX*NBCELLMAX*NBCELLMAX)*rbuf[3] + (NBCELLMAX*NBCELLMAX*NBCELLMAX*NBCELLMAX*NBCELLMAX*NBCELLMAX)*rbuf[4];
  if (nb_ids < NBCELLMAX)
  {
    idents[nb_ids] = temp_id;
    nb_ids ++;
  }
//else
//    forceExit = 1;                            // ce cas n'est pas censé arriver
}


// SI RECU LE PAQUET UPDATE NODE *********************************************************************************
void fonction_10 (unsigned char * rbuf)
{
  int position_pointeur = 3+8*(rbuf[1] + (16^2) * rbuf[2]);
  // ici,on passe les 3 permiers éléments de la liste et on ajoute 8*(...) car il y a des octets supplémentaires lorsqu'un bot est tué ou mange un bot.
  liste *Delete;
  while(node_before_info != NULL)
  {
    Delete = node_before_info;
    node_before_info = Delete->next;
    if(Delete->node->name != NULL) free(Delete->node->name);
    free(Delete->node);
    free(Delete);
  }
  //ici, on a libérée l'espace mémoire occupé par l'ancienne liste chainée
  node_before_info = node_new_info;
  node_new_info = NULL;
  //on copie l'adresse de notre "nouvelle liste chainéé" et on la remplace dans notre ancienn liste chainée
  //on fait pointer node_new_info à NULL car sans ça on aurait par la suité continué la liste chainé (seg fault).
  while(rbuf[position_pointeur] != 0 || rbuf[position_pointeur+1] != 0 || rbuf[position_pointeur+2] != 0 || rbuf[position_pointeur+3] != 0)
  {
    liste *new_adress = malloc(sizeof(liste));
    new_adress->node = malloc(sizeof(node));
    memcpy(new_adress->node, &rbuf[position_pointeur], sizeof(node) - sizeof(char*) - 3 * sizeof(char));
    new_adress->next = node_new_info;
    node_new_info = new_adress;
    position_pointeur += (sizeof(node) - sizeof(char*));
    if (node_new_info->node->flag == 0x0a)
    {
      int len_octet = sizeof(char)*(strlen((char*)&rbuf[position_pointeur]) + 1);
      node_new_info->node->name = malloc(len_octet);
      memcpy(node_new_info->node->name, &rbuf[position_pointeur], len_octet);
      position_pointeur += len_octet;
    }
    else node_new_info->node->name = NULL;
  }
    liste* temp;
  //  int esquive_bord;
    int mode=0;
    x_bot_pos = 0;
    y_bot_pos = 0;
    int size_bot;
    int size_bot_max;
    int found_bot = 1;
    int dist = 7000;
    int dist2 = 7000;
    split_urgence = 0;
    int taille_min = id_petite ();
    int taille_max = id_max ();
    int taille_adversaire;
    if (taille_min == 0) taille_min =idents[0];
      for(temp = node_new_info ; temp != NULL ; temp = temp->next)
      {
        if (found_bot == 1)
        {
          if (temp->node->Id == taille_min)
          {
            x_bot_pos = temp->node->x;
            y_bot_pos = temp->node->y;
            size_bot = temp->node->size;
            if (size_bot_max != 0)
              found_bot =0;
          }
          if (temp->node->Id == taille_max)
          {
            x_bot_pos_max = temp->node->x;
            y_bot_pos_max = temp->node->y;
            size_bot_max = temp->node->size;
            if (size_bot!= 0)
              found_bot =0;
          }
        }
        if (found_bot == 0)
        {
          temp = node_new_info;
          found_bot =3;
        }
        //Si on trouve l'id d'un bot qui n'est pas le notre
        if (temp->node->flag==10 && strcmp (temp->node->name, "Narvalo")!=0)
        {
          //on bascule dans le mode 1 afin de changer notre façon de nous déplacer
          // on désactive le focus des virus
          mode =1;
          virus_no = 1;
          //Dans se If nous allons trouver l'adversaire le plus dangeureux/interressant (c'est à dire le plus proche)
          if (dist2 > distance(x_bot_pos_max,temp->node->x, y_bot_pos_max,temp->node->y))
          {
              taille_adversaire = temp->node->size;
              cursor_bot_x = temp->node->x;
              cursor_bot_y = temp->node->y;
              dist2 = distance(x_bot_pos_max,temp->node->x, y_bot_pos_max,temp->node->y);
            }
          //Ensuite avec 4 if différent nous allons agir diférement en fonction de la taille et de la distance de notre adversaire
          if (dist2 < 2* taille_adversaire)
          {
            if ((taille_adversaire*taille_adversaire)/100> 1.3 * calcul_masse() / nb_ids)
            {
              mode =2;
              split_urgence = 1;
              cursor_bot_x = x_bot_pos_max - (temp->node->x - x_bot_pos_max);
              cursor_bot_y = y_bot_pos_max - (temp->node->y - y_bot_pos_max);
              if (cursor_bot_x < map.X1)
              {
                esquive_bord = fabs (cursor_bot_x - map.X1);
                if (cursor_bot_x - temp->node->x < 0)
                {
                  cursor_bot_y = cursor_bot_y - esquive_bord;
                }
                else
                {
                  cursor_bot_y = cursor_bot_y + esquive_bord;
                }
              }
              if (cursor_bot_x > map.X2)
              {
                esquive_bord = fabs (cursor_bot_x - map.X2);
                if (cursor_bot_x - temp->node->x < 0)
                {
                  cursor_bot_y = cursor_bot_y - esquive_bord;
                }
                else
                {
                  cursor_bot_y = cursor_bot_y + esquive_bord;
                }
              }
              if (cursor_bot_y < map.Y1)
              {
                esquive_bord = fabs (cursor_bot_x - map.Y1);
                if (cursor_bot_y - temp->node->x < 0)
                {
                  cursor_bot_x = cursor_bot_x - esquive_bord;
                }
                else
                {
                  cursor_bot_x = cursor_bot_x + esquive_bord;
                }
              }
              if (cursor_bot_y > map.Y2)
              {
                esquive_bord = fabs (cursor_bot_x - map.Y2);
                if (cursor_bot_y - temp->node->x < 0)
                {
                  cursor_bot_x = cursor_bot_x - esquive_bord;
                }
                else
                {
                  cursor_bot_x = cursor_bot_x + esquive_bord;
                }
            }
            }
          }

          else if ((taille_adversaire*taille_adversaire)/100 > 1.3 * calcul_masse() / nb_ids && dist2 < 2.5 * taille_adversaire)
          {
            mode =2;
            cursor_bot_x = x_bot_pos_max - (temp->node->x- x_bot_pos_max);
            cursor_bot_y = y_bot_pos_max - (temp->node->y- y_bot_pos_max) ;
            if (cursor_bot_x < map.X1)
            {
              esquive_bord = fabs (cursor_bot_x - map.X1);
              if (cursor_bot_x - temp->node->x < 0)
              {
                cursor_bot_y = cursor_bot_y - esquive_bord;
              }
              else
              {
                cursor_bot_y = cursor_bot_y + esquive_bord;
              }
            }
            if (cursor_bot_x > map.X2)
            {
              esquive_bord = fabs (cursor_bot_x - map.X2);
              if (cursor_bot_x - temp->node->x < 0)
              {
                cursor_bot_y = cursor_bot_y - esquive_bord;
              }
              else
              {
                cursor_bot_y = cursor_bot_y + esquive_bord;
              }
            }
            if (cursor_bot_y < map.Y1)
            {
              esquive_bord = fabs (cursor_bot_x - map.Y1);
              if (cursor_bot_y - temp->node->x < 0)
              {
                cursor_bot_x = cursor_bot_x - esquive_bord;
              }
              else
              {
                cursor_bot_x = cursor_bot_x + esquive_bord;
              }
            }
            if (cursor_bot_y > map.Y2)
            {
              esquive_bord = fabs (cursor_bot_x - map.Y2);
              if (cursor_bot_y - temp->node->x < 0)
              {
                cursor_bot_x = cursor_bot_x - esquive_bord;
              }
              else
              {
                cursor_bot_x = cursor_bot_x + esquive_bord;
              }
            }
          }

          else if (3 * (taille_adversaire*taille_adversaire)/100 < calcul_masse() / nb_ids && dist2 < 3*calcul_masse())
            {
              split_attaque = 1;
              mode = 2;
              cursor_bot_x=temp->node->x;
              cursor_bot_y=temp->node->y;
            }

          else if (1.8 * (taille_adversaire*taille_adversaire)/100 < calcul_masse() / nb_ids)
            {
              mode = 2;
              cursor_bot_x=temp->node->x;
              cursor_bot_y=temp->node->y;
            }

          // Les trois dernière ligne sont très importante, en effet sans celle-ci on ne pourrait pas se remettre en mode glouton
          else if (mode == 1)
          {
            mode = 0 ;
          }
          }
        // Ce if nous sert seulement dans le mode desertique car nous avons vu que à partir d'une certaine masse notre bot maigrit très vite
        //Nous controns donc cet effet grace à cette ligne
        if (calcul_masse() > SUPAFAT && found_bot == 2) found_bot = 4;


        if ((found_bot == 3 || found_bot==4) && mode == 0)
        {

          // Nous gerons nos déplcement de nouriture avec seulement 1 seul IF
          if (temp->node->flag == 2)
          {
            food_pos_x = temp->node->x;
            food_pos_y = temp->node->y;
            if (dist > distance(x_bot_pos,food_pos_x, y_bot_pos,food_pos_y))
            {
              dist = distance(x_bot_pos,food_pos_x, y_bot_pos,food_pos_y);
              cursor_pos_x = food_pos_x;
              cursor_pos_y = food_pos_y;
            }
          }
          // Si nous n'avons plus de food autour de nous nous allons aller au centre de la map
          if (dist== 7000)
          {
            cursor_pos_x = map.X2/2;
            cursor_pos_y = map.Y2/2;
          }
          // ce If sert a focus les virus ou pas
          if (size_bot >= SPLITVIRUSMASS && virus_no == 0)
          {
            if (temp->node->flag == 3 && virus_no == 0)
            {
              cursor_pos_x = temp->node->x;
              cursor_pos_y = temp->node->y;
              make_struct_pos (cursor_pos_x,cursor_pos_y);
              break;
            }
          }
        }
        if (mode == 0) make_struct_pos (cursor_pos_x,cursor_pos_y);
      else make_struct_pos (cursor_bot_x,cursor_bot_y);
    }
  }




// Cette fonction renvoie l'id de notre cellule la plus petite
int id_petite ()
{
  int a;
  liste * temp5;
  int taille_minimum=50000;
  for (temp5 = node_new_info; temp5 != NULL ; temp5 = temp5->next )
  {
    for (a=0;a!=16;a++)
    {
      if (temp5->node->Id == idents[a])
      {
        if(temp5->node->size < taille_minimum)
        {
        id_du_bot = idents[a];
        taille_minimum = temp5->node->size;
        }
      }
    }
  }
  return id_du_bot;
}

// Cette fonction renvoie l'id de notre cellule la plus grosse
int id_max ()
{
  int a;
  liste * temp5;
  int taille_maximum=0;
  for (temp5 = node_new_info; temp5 != NULL ; temp5 = temp5->next )
  {
    for (a=0;a!=16;a++)
    {
      if (temp5->node->Id == idents[a])
      {
        if(temp5->node->size > taille_maximum)
        {
        id_du_bot = idents[a];
        taille_maximum = temp5->node->size;
        }
      }
    }
  }
  return id_du_bot;
}


// FONCTION COMPTER_NOS_MORTS -----------------------------------------------------------
// compter_nos_morts sert à enlever parmi nos cellules celles qui auraient pu périr
void compter_nos_morts (unsigned char * paquet, int offset)
{
    nb_morts = paquet[1] + NBCELLMAX*paquet[2];
    i = 0;
    for (i=0; i<nb_morts; i++)                        // la variable i représente le i-ème mort
    {
        p_killed = (int *) &paquet[7+(i*8)];
        killed_temp = (int) *(p_killed);        // killed_temp prend l'identifant du i-ème mort
        j = 0;
        for (j=0;j<=nb_ids;j++)                            // la variable j parcours les identifants de nos cellules
        {
            if (idents[j] == killed_temp)            // si le mort est une de nos cellules ...
            {
                while (j<=nb_ids)
                {
                    idents[j] = idents[j+1];            // on l'enlève de la liste et on déplace tous les autres IDs
                    j++;
                }
                idents[nb_ids] = 0;
                nb_ids--;                        // et on réduit le nombre de nos cellules
        if (nb_ids == 0)
        {
          nb_ids--;                    // ici, on réduit de nouveau pour savoir plus tard si le bot est décédé
        }
            }
        }
    }
}


// Calcul masse -----------------------------------------------------------
int calcul_masse ()
{
  int masse_tot = 0;                          // on initialise la masse totale à 0
  liste * temp_node;
  temp_node = node_new_info;
  while (temp_node != NULL)                   // on parcourt la liste chaînée
  {
    i = 0;
    for (i=0;i<nb_ids;i++)
    {
      if (idents[i] == temp_node->node->Id)   // si une cellule nous appartient
      {
        int mass_cell = ((temp_node->node->size)*(temp_node->node->size))/100;
        masse_tot += mass_cell;               // on ajoute sa masse à la masse totale
      }
    }
    temp_node = temp_node->next;
  }
  if (score_max < masse_tot)                  // on met à jour le score maximal de Narvalo
  {
    score_max = masse_tot;
  }
  return (masse_tot);
}


// Densité de virus -----------------------------------------------------------
int dense_virus ()
{
  int * virus = & virus_present;
  if (* virus != 0)                       // si on sait que la carte contient des virus pas la peine de tester
  {
    return 1;
  }
  else
  {
    liste * temp_node;
    temp_node = node_new_info;
    while (temp_node != NULL)             // sinon on parcourt la liste chaînée
    {
      if (temp_node->node->flag == 3)     // si on trouve un virus ...
      {
        * virus = 1;                      // on met à jour la variable
        return 1;
      }
      temp_node = temp_node->next;
    }
  }
  return 0;
}


// Nombre de food dans l'écran -----------------------------------------------------------
// cette fonction sert à déterminer si l'écran actuel est pauvre en nourriture, que ce soit éphémère ou non
int nb_food_screen ()
{
  int nb_food = 0;
  liste * temp_node;
  temp_node = node_new_info;
  while (temp_node != NULL)           // on parcourt la liste chaînée
  {
    if (temp_node->node->flag == 2)   // si on trouve de la nourriture ...
    {
      nb_food ++;                     // on la compte ...
    }
    temp_node = temp_node->next;
  }
  return (nb_food);                   // puis on renvoie le total
}


// Compter les adversaires -----------------------------------------------------------
// cette fonction sert à déterminer si le bot se trouve seul sur sa carte ou non
void compter_adversaires ()
{
  if (game_mode == 0x01)                  // si le bot est seul jusqu'à présent
  {
    liste * temp_node;
    temp_node = node_new_info;
    while (temp_node != NULL)             // on parcourt la liste chaînée
    {
      if (temp_node->node->flag == 10)    // si on trouve un joueur
      {
        j = 0;
        while (j<nb_ids && temp_node->node->Id != idents[j])
        {                                 // on parcourt la liste de nos cellule ...
          j++;                            // on arrête si un cellule n'est pas à nous
        }
        if (j == nb_ids)                  // si au final, une cellule n'est pas à nous
        {
          game_mode = 0x02;               // alors le bot n'est plus seul
        }
      }
      temp_node = temp_node->next;
    }
  }
}



// FONCTIONS D'ENVOI DE DONNEES **********************************************************
// Return Split -----------------------------------------------------------
unsigned char * return_split ()
{   // la fonction est découpée en deux parties ...
    // tout d'abord, on détermine le nombre de cellule à ne pas dépasser :


  compter_adversaires();        // on cherche des potentiels adversaires
  dense_virus ();               // et des potentiels virus

  if (split_urgence == 1)       // si il faut spliter d'urgence
    nbcellnotoexceed = NBCELLMAX;
  if (split_urgence == 0)
  {
    if (game_mode == 0x02)      // si il y a des adversaires
    {
      if (split_attaque == 1 && attaque_accomplie == 0x00)
      {                         // si on doit attaquer
        attaque_accomplie = 0x01;
        nbcellnotoexceed = nb_ids + 1;
      }
      if (split_attaque == 0 || attaque_accomplie == 0x01)
      {
        nbcellnotoexceed = 1;
        attaque_accomplie = 0x00;
      }
    }
    if (game_mode == 0x01)                  // si on est seul sur la carte
    {
      if (virus_present == 0)               // si il n'y a pas de virus
      {
        if (calcul_masse() >=  SUPAFAT)     // si on est vraiment très gros
          nbcellnotoexceed = 1;
        if (calcul_masse() >= ALONELIMIT)   // si on est un peu avancé
          nbcellnotoexceed = 2;
        if (calcul_masse() < ALONELIMIT)    // si on est petit
        {
          if (nb_food_screen() < ((player.Y2 - player.Y1)/ENVIRODESERT))    // si l'environnement est désert
            nbcellnotoexceed = 1;
          if (nb_food_screen() >= ((player.Y2 - player.Y1)/ENVIRODESERT))   // sinon
            nbcellnotoexceed = 4;
        }
      }
      if (virus_present == 1)                 // si il y'a des virus
      {
        if (calcul_masse() <= SPLITVIRUSMASS) // si notre masse ne permet pas de split sur un virus
        {
          if (nb_food_screen() < ((player.Y2 - player.Y1)/ENVIRODESERT))  // si environnement est désert
            nbcellnotoexceed = 4;
          if (nb_food_screen() >= ((player.Y2 - player.Y1)/ENVIRODESERT)) // sinon
            nbcellnotoexceed = 16;
        }
        if (calcul_masse() > SPLITVIRUSMASS)  // si notre masse permet de split sur un virus
        {
          if (calcul_masse() >= SUPAFAT)      // si on est vraiment très gros
            nbcellnotoexceed = 4;
          if (calcul_masse() < SUPAFAT)       // sinon (dans ce cas, on ira sur un virus pour le manger)
            nbcellnotoexceed = 1;
        }
      }
    }
  }

  // puis, si le nombre de cellule à ne pas dépasser est inférieur au nombre de cellule actuel, on split :
  if (nb_ids < nbcellnotoexceed)               // si le nombre de cellules à ne pas dépasser est supérieur
  {
    liste * temp_node;
    temp_node = node_new_info;
    while (temp_node != NULL)                   // on parcourt la liste chaînée
    {
      i = 0;
      for (i=0;i<nb_ids;i++)                    // on parcourt la liste de nos cellules
      {
        if (idents[i] == temp_node->node->Id)   // lorsqu'on trouve une de nos cellules
        {
          int mass_cell = ((temp_node->node->size)*(temp_node->node->size))/100;
          if (mass_cell >= SPLITPOSSIBLEMASS)   // si la taille de la cellule permet de ce split
          {
            nbcellnotoexceed = 1; // ajout de cette ligne
            return (& split);                   // alors on retourne l'adresse de split, qui vaut 0x11
          }
        }
      }
      temp_node = temp_node->next;
    }
  }
  return (NULL);
}


// Return Nickname -----------------------------------------------------------
unsigned char * return_nickname ()
{
  return (nickname);     // pour rappel, nickname vaut \0Narvalo
}


// Return Dead -----------------------------------------------------------
int return_dead ()
{
  if (nb_ids == -1) return score_max;   // si on a -1 cellule, c'est qu'on est mort
  else return 0;
}
