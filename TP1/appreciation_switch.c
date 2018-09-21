#include <stdio.h>

int main() {
	char i;
	printf("Entrez la note \t");
	scanf ("%c", &i);

	switch (i){ 
	case 'A'	: printf ("Tres Bien !\n"); break;
	case 'B' 	: printf ("Bien\n"); break;
	case 'c' 	: printf ("Assez Bien\n");break;
	case 'D'	: printf ("Passable\n");break;
	case 'E' 	: printf ("Insuffisant\n");break;
	default  : printf("Error\n");
	}
	return (0);

}