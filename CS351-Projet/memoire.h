#include <stdio.h>
#include <stdlib.h>

#define MEMSIZE 32

int memoire[MEMSIZE];


int lectureMem (int * mem, int adresse);		// l est la liste chainée et T le tableau de l'état de la mémoire
void ecritureMem (int * mem, int adresse, int data);
void afficheLMem (int * mem);






/*		ANCIENNE VERSION PAR LISTE CHAINNEE
typedef struct element element;
struct element{
  int data;             // données de 8bits
  int adresseOct;       // adresse de l'octet
  element * suivant;
};
typedef element* liste;

int lectureMem (liste *l, int adresse);		// l est la liste chainée et T le tableau de l'état de la mémoire
int ecritureMem (liste *l, int data);
void afficherListe (liste *l);
*/
