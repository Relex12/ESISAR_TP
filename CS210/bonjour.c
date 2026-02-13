/*---------------------------------------------
		nom du programme : bonjour

But : affiche un message d'accueil sur la sortie standard (écran).
Auteur(s) :
Groupe de TP :
Date de création :
Fichiers sources utilisés : bonjour.c
Commentaires :
----------------------------------------------*/
 #include <stdlib.h>		/*contient la déclaration de EXIT_SUCCESS */
 #include <stdio.h>		/*contient la déclaration de printf */

static void dialogue(void) ;

int main(void)
	{
	dialogue() ;
	return EXIT_SUCCESS ;
	}

void dialogue(void)
	{
	printf("Esisar\n") ;
	printf("bonjour !\n") ;
	}
	

	
	
