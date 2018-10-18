#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 2
#define LIMIT 10

/* indices des éléments dans une matrice 3*3

	0|1|2	
	3|4|5
	6|7|8
*/

void afficherMatrice (int tab[SIZE][SIZE])
{
	for (int i = 0; i < SIZE*SIZE; i++)
	{
		printf("%d", tab[i/SIZE][i%SIZE]);
		if (i%SIZE == SIZE-1) printf("\n");
		else printf("|");
	}
	printf("\n");
}

int** remplirMatrice (int tab[SIZE][SIZE])
{
	for(int i = 0; i < SIZE*SIZE; i++)
	{
		tab[i/SIZE][i%SIZE] = rand() % LIMIT;
	}
	return (tab);
}

int** sommeMatrice (int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE])
{
	for(int i = 0; i < SIZE*SIZE; i++)
	{
		C[i/SIZE][i%SIZE] = A[i/SIZE][i%SIZE] + B[i/SIZE][i%SIZE];
	}
	return (C);
}

int** transposeeMatrice (int A[SIZE][SIZE], int B[SIZE][SIZE])
{
	for(int i = 0; i < SIZE*SIZE; i++)
	{
		B[i%SIZE][i/SIZE] = A[i/SIZE][i%SIZE];
	}
	return (B);
}

int** produitMatrice (int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE])			// problème de résolution du produit matriciel
{
	for(int i = 0; i < SIZE*SIZE; i++)
	{
		C[i/SIZE][i%SIZE] = 0;
		for (int j = 1; j <= SIZE; j++)
		{
			C[i/SIZE][i%SIZE] += A[i/SIZE][(i+j)%SIZE] * B[(i+j)/SIZE][i%SIZE];
		}
	}
	return (C);
}

int main () 
{
	srand(time(NULL));
	int A[SIZE][SIZE];
	int B[SIZE][SIZE];
	int somme[SIZE][SIZE];
	int transpo[SIZE][SIZE];
	int produit[SIZE][SIZE];
	afficherMatrice (remplirMatrice (A));
	afficherMatrice (remplirMatrice (B));
	afficherMatrice (sommeMatrice(A, B, somme));
	afficherMatrice (transposeeMatrice (A, transpo));
	afficherMatrice (produitMatrice(A, B, produit));
	return 0;
}








