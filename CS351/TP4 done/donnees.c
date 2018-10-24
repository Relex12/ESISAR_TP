#include <stdio.h>
#include <stdlib.h>

#define MAX 100


int lireDonnees(char * nomFichier, int T[])
{
	int nb_elements = 0;
	int i = 0;
	FILE * fichier;
	fichier = fopen(nomFichier, "r+");

	if(fichier == NULL)
	{
		perror("Probleme ouverture du fichier : non trouve\ns");
		exit(1);
	}

	while(!feof(fichier))
	{
		fscanf(fichier, "%d", &T[i]);
		i++;
		nb_elements++;
	}
	nb_elements--;

	int fclose(FILE * fichier);
	return (nb_elements);
}

void afficherTableau(int T[], int nb)
{
	for (int i=0; i<nb;i++)	printf("Valeur : %d\n", T[i]);
}

void triABulles(int T[], int nb)
{
	int tmp = 0;
	for (int i=0; i<nb;i++)
	{
		if (T[i-1] > T[i])
		{
			tmp = T[i-1];
			T[i-1] = T[i];
			T[i] = tmp;
		i = 0;
		}
	}
}

void enregistrerDonnees(char * nomFichier, int T[], int nb)
{
	FILE * fichier;
	fichier = fopen(nomFichier, "r+");

	if(fichier == NULL)
	{
		perror("Probleme ouverture du fichier : non trouve\ns");
		exit(1);
	}

	for (int i=0; i<nb;i++)
	{
		fprintf(fichier, "%d ", T[i]);
	}

	int fclose(FILE * fichier);        
}

int main()
{
	int tab[MAX];
	int longueur = lireDonnees("data.txt", tab);
	afficherTableau(tab, longueur);
	triABulles(tab, longueur);
	afficherTableau(tab, longueur);
	enregistrerDonnees("ans.txt", tab, longueur);
	return 0;
}
