# include "math_lib.h"

int quotient (int a, int b)
{
	if (b == 0) 
	{
		printf ("Division par zero impossible\t");
		return (-1); // valeur arbitraire, car quotient ne peut pas prendre en argument des nombres négatifs
	}
	int res = 0;
	while (a-b >= 0)
	{
		a -= b;
		res++ ;
	}
	return (res);
}



int reste (int a, int b)
{
	if (b == 0) 
	{
		printf ("Division par zero impossible\t");
		return (-1); // valeur arbitraire, car quotient ne peut pas prendre en argument des nombres négatifs
	}
	while (a-b >= 0)
	{
		a -= b;
	}
	return (a);
}


int valeurAbsolue (int a)
{
	if (a >= 0) 	return (a);
	else 		return (-a);
}

int ppcm (int a, int b)
{
	return (quotient (valeurAbsolue(a*b), pgcd(a, b)));
}

void testBibliotheque ()
{
	printf ("Section test de quotient ()\n");
	printf ("7 / 2 = %d\n", quotient(7, 2));
	printf ("7 / 0 = %d\n", quotient(7, 0));
	printf ("2 / 7 = %d\n", quotient(2, 7));

	printf ("\nSection test de reste ()\n");
	printf ("7 %% 2 = %d\n", reste(7, 2));
	printf ("7 %% 0 = %d\n", reste(7, 0));
	printf ("2 %% 7 = %d\n", reste(2, 7));

	printf ("\nSection test de valeurAbsolue ()\n");
	printf ("|2| = %d\n", valeurAbsolue(2));
	printf ("|0| = %d\n", valeurAbsolue(0));
	printf ("|-2| = %d\n", valeurAbsolue(-2));

	printf ("\nSection test de ppcm ()\n");
	printf ("ppcm (8, 2) = %d\n", ppcm(8, 2));
	printf ("ppcm (7, 0) = %d\n", ppcm(7, 0));
	printf ("ppcm (63, 128) = %d\n", ppcm(63, 128));
}

int main ()
{
	testBibliotheque ();
	return 0;
}

