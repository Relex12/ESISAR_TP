#include <stdio.h>
#include <stdlib.h>

#define MAX 100


int lireDonnees(char * nomFic, int T[])
{
    int nb_elements = 0;
    int i = 0;
    FILE * fic;
    fic = fopen(nomFic, "r+");

    if(fic == NULL)
    {
        perror("Probleme ouverture fichier monFichier.txt");
        exit(1);
    }

    while(!feof(fic))
    {
        fscanf(fic, "%d", &T[i]);
        i++;
        nb_elements++;
    }
    nb_elements--;

    int fclose(FILE * fic);
    return (nb_elements);
}

void afficherTableau(int T[], int nb)
{
    int i =0;
    for (i=0; i<nb;i++)
        printf("Valeur : %d\n", T[i]);
}

void triABulles(int T[], int nb)
{
    int i = 0;
    int tmp = 0;
    while (i<nb-1)
    {
        i++;
        if (T[i-1] > T[i])
        {
            tmp = T[i-1];
            T[i-1] = T[i];
            T[i] = tmp;
            i = 0;
        }
    }
}

/*void enregistrerDonnees(char * nomFich, int T[], int nb)
{
        
}
*/
int main()
{
    int tab[MAX];
    int longueur = lireDonnees("MonFichier.txt", tab);
    afficherTableau(tab, longueur);
    triABulles(tab, longueur);
    printf("\n\t tri accompli\n");
    afficherTableau(tab, longueur);
    return 0;
}
