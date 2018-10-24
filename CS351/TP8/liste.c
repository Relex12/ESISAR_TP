#include <stdio.h>
#include <stdlib.h>

typedef struct element element;
struct element 
	{
		int valeur; /* valeur de l’élément */
		element* suivant; /* adresse du successeur */
	};

typedef element* liste;


liste* addHead (liste* l, int nombre)
{
	element *e = (element* ) malloc(sizeof(element));
	e->valeur = nombre;
	e->suivant = *l;
	*l = e;
	return l;
}


liste* addTail (liste* l, int nombre)
{
	element *e = (element* ) malloc(sizeof(element));

	element *temp = *l;
	while (temp->suivant != NULL)
	{
		temp = temp->suivant;
	}

	e->valeur = nombre;
	e->suivant = temp->suivant;
	temp->suivant = e;
	return l;
}


liste* insertElement (liste* l, int nombre)
{
	element *e = (element* ) malloc(sizeof(element));

	element *temp = *l;
	element *prec = NULL;
	while (temp != NULL && temp->valeur <= nombre)
	{
		prec = temp;
		temp = temp->suivant;
	}

	e->valeur = nombre;
	e->suivant = temp;
	prec->suivant = e;
	return l;

}

void afficherListe(liste * l)
{
	element *temp = *l;
	while (temp != NULL)
	{
		printf ("%d ", temp->valeur);
		temp = temp->suivant;
	}
	printf ("\n");
}

void supprElement (int nb, liste * l)
{
	int i = 0;
	element *temp = *l;
	element *prec = *l;
	while (temp != NULL && i < nb)
	{
		i++;
		if (nb == 1)		*l = temp->suivant;
		else if (i == nb) 	prec->suivant = temp->suivant;
		else 			prec = temp;
		temp = temp->suivant;
	}
	if (i < nb) 			printf ("Liste trop courte\n");
}

int main ()
{
	liste L = NULL; 	/* L contient l’adresse du premier élément de la liste */
	addHead (&L, 50);
	addHead (&L, 40);
	addTail (&L, 60);
	insertElement (&L, 55);
	afficherListe(&L);

	supprElement (4, &L);
	afficherListe(&L);
	return 0;
}
