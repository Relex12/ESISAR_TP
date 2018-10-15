#include <stdio.h>

//	version plus abrégée

/*int fibonacci (n) {
	if (n == 1 || n == 0) return (n);
	else return (fibonacci (n-1) + fibonacci (n-2));
}
*/

int fibonacci (n) {
	int minusTwo = 0;
	int minusOne = 1;
	int temp;

	while (n > 1) {
		temp = minusOne + minusTwo;
		minusTwo = minusOne;
		minusOne = temp;
		n--;
	}
	return (minusOne);
}

int main() {
	int n = 0;
	printf("Entrez un nombre : \t");
	scanf ("%d", &n);
	printf ("Le %d-ème terme de la suite de Fibonacci est : %d\n", n, fibonacci(n));
	return (0);
}
