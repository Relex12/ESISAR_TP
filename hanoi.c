#include <stdio.h>

void hanoi (int n, char d, char a, char i)
  if (n != 0)
  {
    hanoi (n-1, d, i, a);
    printf ("déplacement : %c vers %c\n", d, a)
    hanoi (n-1, i, a, d);
  }
}

int main (){
	int n = 0;
	printf("Entrez une valeur de n : \n");
	scanf ("%d", &n);

  printf("DEBUT DES DEPLACEMENTS DE HANOI\n");
  hanoi (n, 'A', 'B', 'C');
  printf("FIN DES DEPLACEMENTS DE HANOI\n");

// jamais testée
  return (0);
}
