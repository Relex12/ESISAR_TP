#include <stdlib.h>
#include <stdio.h>

#include <time.h>

typedef struct Client {
	int numero;
	int prixAppel;
	int nbAppel;
	struct Client * suivant;
} client;

// Nombre total de lignes dans le fichier
#ifndef NBLOGLINE
#define NBLOGLINE    2000000
#endif

// Nombre de clients
	#ifndef NBCLIENT
#define NBCLIENT    20000
#endif




struct Client *createClient(int numero, int prixAppel)
{
	client* liste;
	if ( (liste = malloc(sizeof(client)) ) == NULL) return NULL;
	liste->numero = numero;
	liste->prixAppel = prixAppel;
	liste->nbAppel = 1;
	liste->suivant = NULL;
	return liste;
}

int addLogLine(struct Client **liste, int numero, int prixAppel)
{
	client* maliste = *liste;
	client* nouvelelem;
	if  (maliste == NULL) {
		if ( ( *liste = createClient(numero,prixAppel) ) == NULL){
			printf("echec du a un manque de place");
			return 0;
		}
		else {
			return 1;
		}
	}
	else {
		if( maliste->numero == numero) {
				maliste->prixAppel += prixAppel;
				maliste->nbAppel ++;
		}
		else{
			if( maliste->numero > numero){
				if( (nouvelelem = createClient(numero,prixAppel)) == NULL) return 0;
				nouvelelem->suivant = *liste;
				*liste = nouvelelem;
			}
			else{
				while( maliste->suivant != NULL && ( maliste->suivant)->numero <= numero) maliste = maliste->suivant;
				if( maliste->numero == numero) {
					(*liste)->prixAppel += prixAppel;
					(*liste)->nbAppel ++;
				}
				else{
					if ( (nouvelelem = createClient(numero,prixAppel)) == NULL) return 0;
					nouvelelem->suivant = maliste->suivant;
					maliste->suivant = nouvelelem;
				}
			}
		}
	}
	return 1;
}

void dumpListe(struct Client *liste)
{
	while (liste != NULL) {
		printf("numero : %d\tprix des appels : %d\tnombre d'appels : %d\n",liste->numero,liste->prixAppel,liste->nbAppel);
		liste = liste->suivant;
	}
}


int main()
{
    client *liste=NULL;

    int i;
    int numeroTel;
    int prixAppel;
	//calcul du temps
	clock_t  t1,t2;
	float temps;
    // Aide au calcul du pourcentage d'avancement
    int pas = NBLOGLINE/100;

	srand(time(NULL));

	//debut du temps
	t1 = clock();
    printf("****** Facturation appels telephoniques ******\n");


    for(i=0;i<NBLOGLINE;i++)
    {

        // Génération d'un numéro de telephone portable
        numeroTel = 600000000+(rand() % NBCLIENT);

        // Donne un prix d'appel compris entre 0.01 et 4 euros
        prixAppel = (rand() % 400)+1;

        // Ajout de cette ligne de log dans la liste des clients

		if (!addLogLine(&liste ,numeroTel,prixAppel)) {
			printf("exit failure");
			break;
			}
        //printf("numero=%d prix = %d\n",numeroTel,prixAppel);


        // Affichage du pourcentage d'avancement
        if ((i % pas)==0)
        {
             printf("Done  = %d %%...\n",i/pas);
        }
    }

   dumpListe(liste);
   printf("======= Facturation appels telephoniques ======\n");

   //fin du temps
   t2 = clock();
   temps = (float)(t2-t1)/CLOCKS_PER_SEC;
   printf("temps d'execution = %f sec\n", temps);
   return 0;
}
