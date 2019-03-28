#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct Client {
	int numero;
	int prixAppel;
	int nbAppel;
	struct Client * gauche;
	struct Client * droite;

} client;

// Nombre total de lignes dans le fichier
#ifndef NBLOGLINE
#define NBLOGLINE    200000
#endif
// Nombre de clients
#ifndef NBCLIENT
#define NBCLIENT    2000
#endif



struct Client * creerClient(int numeroTel, int nbAppel,int cout)
{
	client * liste = NULL;
	if ((liste = malloc(sizeof(client))) == NULL)  return NULL;
	liste->numero = numeroTel;
	liste->nbAppel = nbAppel;
	liste->prixAppel = cout;
	liste->gauche = NULL;
	liste->droite = NULL;
	return liste;
}

struct Client * chercher (struct Client * abr,int numeroTel)
{
	client * parcourt = NULL;
	parcourt = abr;

	if (parcourt == NULL)						return NULL;

	while (parcourt->numero != numeroTel)
	{
		if (parcourt->numero < numeroTel)
		{
			if (parcourt->droite == NULL)		return NULL;
			else								parcourt = parcourt->droite;
		}
		else if (parcourt->numero > numeroTel)
		{
			if (parcourt->gauche == NULL)		return NULL;
			else								parcourt = parcourt->gauche;
		}
	}

	return parcourt;
}

struct Client *inserer(struct Client ** abr, int numeroTel, int prixAppel)
{
    client * parcourt = NULL;
    client * insertion = NULL;
    parcourt = *abr;

	if( (insertion = chercher(parcourt,numeroTel) ) != NULL) {
		insertion->nbAppel += 1;
		insertion->prixAppel += prixAppel;
		return *abr;
	}

	if (parcourt == NULL)
	{
		if((*abr = malloc(sizeof(client))) == NULL) 	return NULL;
		*abr = creerClient(numeroTel, 1, prixAppel);
		return *abr;
	}
	while (parcourt->numero != numeroTel)
	{
		if (parcourt->numero < numeroTel)
		{
			if (parcourt->droite == NULL)
			{
				if((insertion = malloc(sizeof(client))) == NULL) 	return NULL;
				insertion = creerClient(numeroTel, 1, prixAppel);
				parcourt->droite = insertion;
				return *abr;
			}
			else								parcourt = parcourt->droite;
		}
		else if (parcourt->numero > numeroTel)
		{
			if (parcourt->gauche == NULL)
			{
				if((insertion = malloc(sizeof(client))) == NULL) 	return NULL;
				insertion = creerClient(numeroTel, 1, prixAppel);
				parcourt->gauche = insertion;
				return *abr;
			}
			else								parcourt = parcourt->gauche;
		}
	}
	return NULL;
}

struct Client *supprimerClient(struct Client ** abr, int numeroTel)
{
	client * parcourt = NULL;
	client * suppression = NULL;
	client * temp = NULL;
	parcourt = *abr;

	if (parcourt == NULL) 						return NULL;
	if(parcourt->numero == numeroTel){								//cas racine a supprimer
		if (parcourt->gauche == NULL) {
			suppression = *abr;
			*abr=parcourt->droite;			// si la racine a un fils droite
			return suppression;
		}
		else if(parcourt->droite == NULL){
			suppression = *abr;
			*abr=parcourt->gauche;			// si la racine a un fils gauche
			return suppression;
		}
		else{														// si la racine a deux fils
			suppression = parcourt;
			parcourt = parcourt->droite;
			if(parcourt->gauche == NULL) {
				parcourt->gauche = suppression->gauche;
				*abr = parcourt;
				return suppression;
			}
			while(parcourt->gauche != NULL)		parcourt= parcourt->gauche;
			temp = parcourt->gauche;
			parcourt->gauche = temp->droite;
			temp->gauche = suppression->gauche;
			temp->droite = suppression->droite;
			*abr = temp;
			return suppression;
		}
	}

	while (parcourt->numero != numeroTel)		// on cherche l'élément à supprimer
	{
		if (parcourt->numero > numeroTel)
		{
			if (parcourt->gauche == NULL)		return NULL;
			else
			{
				suppression = parcourt;
				parcourt = parcourt->gauche;
			}
		}
		else if (parcourt->numero < numeroTel)
		{
			if (parcourt->droite == NULL)		return NULL;
			else
			{
				suppression = parcourt;
				parcourt = parcourt->droite;
			}
		}
	}

	// ici parcourt continent l'élément à supprimer et suppression contient son père

	if ((parcourt->gauche == NULL) || (parcourt->droite == NULL))			// si parcourt a un ou 0 fils
	{
		if (parcourt->gauche == NULL)																// si parcourt n'a qu'un fils à droite
		{
			if (suppression->numero < numeroTel)	suppression->droite = parcourt->droite;			// si parcourt est à gauche de suppression
			else 									suppression->gauche = parcourt->droite;			// si parcourt est à droite de suppression
			return parcourt;
		}
		else																						// si parcourt n'a qu'un fils à gauche
		{
			if (suppression->numero < numeroTel)	suppression->droite = parcourt->gauche;			// si parcourt est à gauche de suppression
			else 									suppression->gauche = parcourt->gauche;			// si parcourt est à droite de suppression
			return parcourt;
		}

	}

	else 																		// si parcourt a deux fils
	{
		parcourt = parcourt->droite;
		if(parcourt->gauche == NULL) {
			parcourt->gauche = suppression->droite->gauche;
			temp = suppression->droite;
			suppression->droite = parcourt;
			return temp;
		}
		while(parcourt->gauche != NULL)		parcourt= parcourt->gauche;
		temp = parcourt->gauche;
		parcourt->gauche = temp->droite;
		parcourt = suppression->droite;
		temp->gauche = parcourt->gauche;
		temp->droite = parcourt->droite;
		suppression->droite = temp;
		return parcourt;
	}

}



void parcourirInfixe(struct Client * abr)
{
	if (abr != NULL)
	{
		if (abr->gauche != NULL)		parcourirInfixe(abr->gauche);
		printf("numero : %d \tcout : %d \tnbAppel : %d\n", abr->numero, abr->prixAppel, abr->nbAppel);
		if (abr->droite != NULL)		parcourirInfixe(abr->droite);
	}
}

struct Client * creerArbre()
{
	client * liste = creerClient(15, 0, 0);						// couche 1
	liste->gauche = creerClient(12, 0, 0);						// couche 2
	liste->droite = creerClient(20, 0, 0);
	liste->gauche->gauche = creerClient(8, 0, 0);				// couche 3
	liste->gauche->droite = creerClient(14, 0, 0);
	liste->droite->gauche = creerClient(16, 0, 0);
	liste->droite->droite = creerClient(21, 0, 0);
	liste->gauche->gauche->droite = creerClient(10, 0, 0);		// couche 4
	liste->gauche->droite->gauche = creerClient(13, 0, 0);
	liste->droite->gauche->droite = creerClient(17, 0, 0);
	return liste;
}
int test ()
{
	printf("------ SECTION TEST -------\n");


	client * listeTest=NULL;
	listeTest = creerArbre();

	printf("parcourt infixe de l'ABR cree\n");
	parcourirInfixe(listeTest);


	printf("\ntest de chercher\n");

	client * var = NULL;

	for (int j = 6; j <= 22 ; j ++)
	{
		var = chercher (listeTest, j);
		if (var == NULL)	printf("valeur %d non présente dans l'ABR\n", j);
		else				printf("valeur %d trouvée : %d\n", j, var->numero);
	}

	printf("\ntest de inserer\n");

	inserer(&listeTest, 5, 0);
	inserer(&listeTest, 19, 0);
	inserer(&listeTest, 22, 0);
	printf("ajout de 5, 19 et 22\n");
	parcourirInfixe(listeTest);

	printf("\ntest de supprimer\n");

	supprimerClient(&listeTest, 10);
	supprimerClient(&listeTest, 14);
	supprimerClient(&listeTest, 21);
	supprimerClient(&listeTest, 20);
	printf("suppression de 10, 14, 21\n");
	parcourirInfixe(listeTest);

	printf("------ SECTION TEST -------\n");
	return 0;
}


int main()
{
	float temps;
	clock_t t1, t2;
	t1 = clock();


    client *liste=NULL;


    int i;
    int numeroTel;
    int prixAppel;


    // Aide au calcul du pourcentage d'avancement
    int pas = NBLOGLINE/100;

	////////////
	srand(time(NULL));
	////////////
    for(i=0;i<NBLOGLINE;i++)
    {

        // Génération d'un numéro de telephone portable
        numeroTel = 600000000+(rand() % NBCLIENT);

        // Donne un prix d'appel compris entre 0.01 et 4 euros
        prixAppel = (rand() % 400)+1;

        // Ajout de cette ligne de log dans la liste des clients
   	if (inserer(&liste ,numeroTel,prixAppel)==NULL) break;
        // Affichage du pourcentage d'avancement
        if ((i % pas)==0)
        {
             printf("Done  = %d %%...\n",i/pas);
        }
    }


    printf("****** Facturation appels telephoniques ******\n");

    parcourirInfixe(liste);

    printf("****** Suppression de la facturation appels telephoniques ******\n");


    for (i=0;i<NBCLIENT;i++)
	{
		client *tmp=NULL;
		if ((tmp=supprimerClient(&liste,600000000+i)) != NULL)  free(tmp);
    }
    printf("****** Fin Facturation appels telephoniques ******\n");

	test();

	t2 = clock();
	temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	printf("temps total du mail = %f\n", temps);

	return 0;
}
