#include <stdio.h>

int main() {
	char i;
	printf("Entrez la note \t");
	scanf ("%c", &i);
	if (i == 'A') 	printf ("Tres Bien !\n");
	else if (i == 'B') 	printf ("Bien\n");
	else if (i == 'c') 	printf ("Assez Bien\n");
	else if (i == 'D')	printf ("Passable\n");
	else 	printf ("Insuffisant\n");

	return (0);

}