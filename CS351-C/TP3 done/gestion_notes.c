# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define TAILLE 5


// NB : il serait plus rapide de réaliser un unique programme responsable du calcul de toutes valeurs, que l'on pourrait écrire dans un tableau de réponse pour garder les résultats


void afficherNotes(double tab[]) 
{
	printf("|");
	for (int i = 0; i < TAILLE; i++)	printf("%f|", tab[i]);
	printf("\n");		
}

double minimumNote(double tab[]) 
{
	double min = tab[0];
	for (int i = 0; i < TAILLE; i++)	if (tab[i] < min) 	min = tab[i];
	return min;
}

double maximumNote(double tab[]) 
{
	double max = tab[0];
	for (int i = 0; i < TAILLE; i++)	if (tab[i] > max) 	max = tab[i];
	return max;
}

double calculMoyenne(double tab[]) 
{
	double moy = 0;
	for (int i = 0; i < TAILLE; i++)	moy += tab[i];
	return (moy / TAILLE);
}

double calculVariance(double tab[]) 
{
	double var = 0, moy = calculMoyenne(tab);
	for (int i = 0; i < TAILLE; i++)	var = var + ((tab[i] - moy) * (tab[i] - moy));
	return (var / TAILLE);
}

double calculEcartType(double tab[]) 
{
return (sqrt(calculVariance(tab)));
}

int rechercherValeur(double tab[], double nombre) 
{
	for (int i = 0; i < TAILLE; i++)	if (tab[i] > nombre)	return (i);
	return (-1);
}

void test_gestion (double tab[TAILLE])
{
	afficherNotes(tab);
	printf ("note basse = %f\n", 	minimumNote(tab));
	printf ("note haute = %f\n", 	maximumNote(tab));
	printf ("moyenne = %f\n", 	calculMoyenne(tab));
	printf ("variance = %f\n", 	calculVariance(tab));
	printf ("ecart type = %f\n", 	calculEcartType(tab));
}


int main ()
{
	double notes1[TAILLE] = {12.0, 13.5, 8.5, 14.7, 6.0};
	test_gestion (notes1);
	double notes2[TAILLE] = {3.5, 19.5, 13.8, 10.7, 16.2};
	test_gestion (notes2);
	double notes3[TAILLE] = {10, 10, 10, 10, 10};
	test_gestion (notes3);
	return 0;
}
