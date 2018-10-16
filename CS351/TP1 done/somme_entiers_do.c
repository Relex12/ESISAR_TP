#include <stdio.h>

int main() {
	int i;
	int res =0;
	int n=0;
	printf("Entrez lune valeur entiere \t");

	scanf ("%d", &i);
	do 
	{
		res +=n;
		n++;
	}while (n != i);
	res +=n;
	printf ("La somme des %d premiers entiers est %d\n", i, res);
	return (0);

}