#include <stdio.h>

int pgcd (a, b) {
	if (b == 0) return (a);
	else return (pgcd (b, a%b));
}

int main() {
	int a = 0;
	int b = 0;
	printf("Entrez deux nombres : \n");
	scanf ("%d", &a);
	scanf ("%d", &b);
	printf ("Le PGCD de %d et %d est : %d\n", a, b, pgcd (a, b));
	return (0);
}
