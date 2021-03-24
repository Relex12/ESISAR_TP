#include <stdio.h>

int main() {
	char i;
	printf("Entrez la note \t");
	scanf ("%c", &i);
	if (i == 'A') 	printf ("Tres Bien !\n");
	if (i == 'B') 	printf ("Bien\n");
	if (i == 'c') 	printf ("Assez Bien\n");
	if (i == 'D')	printf ("Passable\n");
	if (i == 'E') 	printf ("Insuffisant\n");

	return (0);

}