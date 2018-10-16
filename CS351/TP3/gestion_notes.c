# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define TAILLE 5

void gestion (double tab[TAILLE])
{
	double basse = tab[0];
	double haute = tab[0];
	double moyenne = 0; 
	double variance = 0;
	double ecart_type = 0;

	int i = 0;
	while (i < TAILLE )
	{
		if (tab[i] < basse) basse = tab[i];
		if (tab[i] > haute) haute = tab[i];
		moyenne = moyenne + (tab[i] / TAILLE);
		i++;
	}

	i = 0;
	while (i < TAILLE )
	{
		variance = variance + ((tab[i] - moyenne ) * (tab[i] - moyenne ));
		i++;
	}
	
	variance = variance / TAILLE;
	ecart_type = sqrt(variance);

// 	assignation

	tab[0] = basse; 
	tab[1] = haute; 
	tab[2] = moyenne; 
	tab[3] = variance; 
	tab[4] = ecart_type; 
}


int test_gestion ()
{
	double notes[TAILLE] = {12.0, 13.5, 8.5, 14.7, 6.0};
	gestion (notes);
	printf ("note basse = %f\n", notes[0]);
	printf ("note haute = %f\n", notes[1]);
	printf ("moyenne = %f\n", notes[2]);
	printf ("variance = %f\n", notes[3]);
	printf ("ecart type = %f\n", notes[4]);

	return 0;
}


int main ()
{
	test_gestion ();
	return 0;
}
