# ifndef MENUUTIL_H
# define MENUUTIL_H
#include <stdbool.h>
/*------------------------------------------------------------------------------
			nom : afficheSuite

Prototype : */
extern void afficheSuite(void) ;

/*   	But :	affiche à l'écran les premiers termes de la suite 1
			(voir définition de la suite et NBTERMES dans le sujet)
	Entrées (données) : aucune 
	Sortie (résultats) :	aucun : c'est une procédure !
	Algo/ Commentaires particuliers : cf TD
   Paramètres : 
	Valeur rendue : 
	Précondition :							
	Postcondition :						
---------------------------------------------------------------------*/
/*------------------------------------------------------------------------------
			nom : estBissextile

Prototype : */
extern bool estBissextile(int m) ;

/*   	But :	vérifie si l'année donnée est bissextile
	Entrées (données) : le millésime de l'année (entier)
	Sortie (résultats) :	l'état bissextile ou non (booleen)
	Algo/ Commentaires particuliers : --
   Paramètres :		 m : le millésime 
	Valeur rendue :	 vrai (true) si "m" est bissextile
	Précondition :		 m >= 0						
---------------------------------------------------------------------*/
# endif
