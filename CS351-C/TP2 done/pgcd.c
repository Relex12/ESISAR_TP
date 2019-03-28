# include "math_lib.h"

int pgcd (int a, int b) {

	if (b == 0) return (a);
	int r;
	while (b != 0) {
		r = a%b;
		a = b;
		b = r;	
#ifdef MISEAUPOINT
		printf ("Ici : b = %d \n", b);	
#endif
	}
	return (a);
}

#ifndef LIBRARY 		// utilisé pour l'exercice 3
int main() {
	int a = 0;
	int b = 0;
	printf("Entrez deux nombres : \n");
	scanf ("%d", &a);
	scanf ("%d", &b);
	printf ("Le PGCD de %d et %d est : %d\n", a, b, pgcd (a, b));
	return (0);
}
#endif
