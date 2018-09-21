#include <stdio.h>

int factorielle (n) {
	int res = 1;
	while (n > 1) {
		res = res * n;
		n--;
	}
	return (res);
}

int factorielleBis (m) {
	int n = 1;
	int facto = 1;
	while (facto <= m) {
		n++;
		facto = facto * n;
	}
	return (n);
}

int main() {
	int n = 0;
	printf("Entrez un nombre : \n");
	scanf ("%d", &n);
	int nombre = factorielleBis(n); // on le stocke pour ne pas avoir à le calculer 3 fois
	printf ("factorielle(%d) = %d\nfactorielleBis(%d) = %d\n", n, factorielle(n), n, nombre);
	printf ("factorielle(%d) = %d\n", nombre, factorielle(nombre));
	return (0);
}
