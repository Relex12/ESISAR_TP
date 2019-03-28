#include <stdio.h>

#define SIZE 15

void affiche_tab (int* tab) 
{
	printf("tab contient : \t");
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", tab[i]);
	}
	printf("\n");
}

void echange (int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void trih (int* tab) 
{
	int b = 0, w = 0, r = SIZE-1;

	while (w <= r)
	{
		if (tab[w] < 3)				// bleu
		{
			echange (&tab[b], &tab[w]);
			b ++;
			w ++;
		}
		else if (tab[w] >= 3 && tab[w] < 6)	// blanc
		{
			w++;
		}
		else {					// rouge
			echange (&tab[w], &tab[r]);
			r --;
		}
//	affiche_tab (tab);
	}
}

int main ()
{
	int tab[SIZE] = {5, 8, 1, 4, 3, 9, 2, 7, 3, 8, 1, 4, 5, 3, 8};
	printf ("avant tri ");
	affiche_tab (tab);
	trih (tab);
	printf ("apres tri ");
	affiche_tab (tab);
	return 0;
}


/*

Début
	b ←1; w ←1 ; r ←n
		tant que w ≤ r faire 
			si T[w] = blanc alors w ←w+1
			sinon si T[w] = bleu alors 
			{
				échanger T[b] et T[w] ; 
				b ←b+1 ; w ←w+1
			}
			sinon // T[w] = rouge 
			{
				échanger T[w] avec T[r] ; 
				r ←r-1
			}
		fintantque ;
Fin

*/
