#include <stdio.h>

int fibonacci (int n) {	
  if (n <= 0) return (0);
	else if (n <= 2) return (1);
	else return (fibonacci(n-1) + fibonacci(n-2));
}

int main {
  int n = 0;
  printf ("Entrez une valeur pour n :\t");
  scanf ("%d", &n);
  printf ("le %ème terme de la suite de Fibonacci est : %d", n, fibonacci(n));
  return (0);
}
