#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "menuUtil.h"

/* Exemple de commentaires demandés pour un programme :
	(sera mis dans le fichier source contenant la fonction "main") :*/
/*---------------------------------------------
		nom du programme : menu

But : programme proposant plusieurs choix à l'opérateur. 
		(Voir spécifs dans le sujet du TP)
Auteur(s) : 	A COMPLETER
Groupe de TP : A COMPLETER
Fichiers sources (".c" et ".h") créés (et fournis) : menu.c menuUtil.c menuUtil.h
Autres fichiers (non standard) utilisés : duccinio.o (bibliothèque d'entrées sorties)
bibliothèques standard utilisées : stdio, stdlib, stdbool, time, assert
Commentaires :
	- Entrées/sorties (entrées opérateur, affichages divers,
			fichiers textes ou binaires utilisés ou créés, bref toute explication
			nécessaire à la lecture de vos sources
	- Algo particuliers
	- Etat d'avancement :	à l'état de squelette : A COMPLETER
----------------------------------------------*/
/* vous devrez en outre pour chaque fonction ou procédure crée donner :
- son nom
- son but
- son prototype
- décrire les paramètres, la valeurs de retour, les pré-conditions éventuelles.
NB : pour certains TP (notament les premiers), toutes les routines sont spécifiées,
les commentaires sont déjà fournis...(essayez de vous en inspirer pour la suite)

De façon générale, sinon,ce que je demande en tant que "commentaires" c'est :
- indiquer clairement pour chaque déclaration de variable ce que c'est, à quoi
elle sert.
- commenter de même les constantes, les structures de données.
- donner des noms de variables et de routines explicites.
- éventuellement rajouter quelques commentaires pour clarifier le fonctionnement
"global" du programme, si nécessaire.
*/

/* Quelques constantes symboliques pour éviter les erreurs lors de
			 modifications futures de spécifications */
#define NBHELLO_MIN	0
#define NBHELLO_MAX	20
#define MILLESIME_MIN	1582
#define MILLESIME_MAX	3000

/* déclaration de référence (signature, prototype) de la procédure afficheMenu() */	
static void afficheMenu(void) ;
static void purgeStdin(void) ;

/* l'exécutable démarre ici */
int main(void)
	{
	char choix ;		/* caractère choisi par l'opérateur */
	bool fini ;			/* drapeau du SCD */
	int m ;				/* variable (temporaire) pour millésime */
	
	fini = false ;
	
	while ( ! fini )
		{									/* début du "tant que" */
		afficheMenu() ;
	   (void) scanf("%s",&choix) ;/* berk, pas de test d'erreur */
		purgeStdin() ;
		switch (  choix )
			{									/* début du "selon" */
			case 's' :							/* cas choix = 's' ou 'S' */
			case 'S' :
				printf(" **** suite 1 : \n") ;
/*				afficheSuite() ; 			A "dé-commenter" */
				break;
			case 'b' :							/* cas choix = 'b' ou 'B' */
			case 'B' :
				printf(" **** Bissextile ? : \n") ;
				printf(" **** Donnez le millésime? (entre %d et %d) : ",
														MILLESIME_MIN, MILLESIME_MAX) ;
				/* faire saisir ici un entier à l'opérateur,
						à mettre dans la variable "m" */
/*
				if ( estBissextile(m) )
					printf("l'année %d est bissextile\n",m) ;
				else
					printf("l'année %d n'est pas bissextile\n",m) ;
*/
				break;
			case 'q' :							/* cas choix = 'q' ou 'Q' */
			case 'Q' :
				printf("****** quitter : \n") ;
				fini = true ;
				break;
			default :								/* autres cas */
				printf("prenez RDV chez l'opticien choix =%d\n",choix) ;
			}										/* fin du "selon" */
		}										/* fin du "tant que" */
	printf("BYE\n") ;
	return EXIT_SUCCESS ;
	}

/* déclaration de définition de la procédure afficheMenu() */	
static void afficheMenu(void)
	{
	printf("*******\nPremier Menu écrit en C : \n") ;
	printf("suite1 : tapez s\n") ;
	printf("bissextile : tapez b\n") ;
	printf("quitter : tapez q\n") ;
	printf("Votre choix ? : ") ;
	}

/* déclaration de définition de la procédure purgeStdin():
	scanf laisse des caractères dans le buffer d'entrée. Pour les premiers TP, on pourra utiliser
	cette verrue, que je déconseille par la suite (ainsi que l'utilisation de getc, gets... */	
static void purgeStdin(void) {
	char c ;				/* pour nettoyage buffer d'entrée */
		while ( (c = getchar()) != '\n' && c != EOF ) ; /* purge le buffer d'entrée (nb : berk!!!) */
	}


	
	
