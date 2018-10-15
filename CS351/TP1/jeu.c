#include <stdio.h>

#define MAX 5

int jeuMulti(n) {
	int i = 0;
	int ans = 0;
	while ( (ans == (n*i) ) && (i < MAX) ) {
		i++;
		printf ("%d x %d =\t", i, n);
		scanf ("%d", &ans);
	}
	if (i == 12) printf ("Bravo, tu as gagne\n");
	else printf ("Perdu, le resultat est %d\n", (n*i));

	return (0);
}


int jeuMultiPoints(n) {
	int i = 0;
	int ans = 0;
	int nb_err = 0;
	while (i < MAX) {
		i++;
		printf ("%d x %d =\t", i, n);
		scanf ("%d", &ans);
		if (ans != (n*i)) nb_err++;
	}
	printf ("Bravo, tu as fait %d faute(s)\n", nb_err);

	return (0);
}

int main() {
	int n = 0;
	while (n < 1 || n > 9) {
		printf("Entrez un nombre entre 1 et 9 : \n");
		scanf ("%d", &n);
	}
	jeuMulti(n);
	jeuMultiPoints(n);
	return (0);
}
