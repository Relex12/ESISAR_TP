#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define SIZE 100000
#define VALMAX 100

void afficheTab (int * tab) {
    printf("affichage tableau :\t");
    for (int i = 0; i < SIZE; i++)     printf("%d\t", tab[i]);
    printf("\n");
}

void remplirTab (int * tab) {
    srand(time(NULL)); 
    for (int i = 0; i < SIZE; i++)     tab[i] = rand() % VALMAX;
}

void triInsertion(int * tab){
    int valeur, j;
    for (int i = 1; i < SIZE; i ++){
        valeur = tab[i];
        j = i;
        while (j > 0 && valeur < tab[j-1]) {
            tab[j] = tab[j-1];
            j--;
        }
        tab[j] = valeur;
    }
}

void triSelection(int * tab){
    int ppetit, temp;
    for (int i = 0; i < SIZE; i ++){
        ppetit = i;
        for (int j = i; j < SIZE; j ++){
            if (tab[j] < tab[ppetit])       {
                ppetit = j;
            }
        }
        temp = tab[i];
        tab[i] = tab[ppetit];
        tab[ppetit] = temp;
    }
}

int main(int argc, char const *argv[]) {
    int tab[SIZE];
    printf("debut du programme\n");
    remplirTab(tab);

    float temps;
    clock_t t1, t2;

    t1 = clock();
    triInsertion(tab);
    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps insertion = %f\n", temps);

    remplirTab(tab);

    t1 = clock();
    triSelection(tab);
    t2 = clock();
    temps = (float)(t2-t1)/CLOCKS_PER_SEC;
    printf("temps selection = %f\n", temps);
    return 0;
}
