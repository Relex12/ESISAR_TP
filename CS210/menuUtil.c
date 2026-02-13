#include <stdio.h>
#include <assert.h>
#include "menuUtil.h"

/* constantes pour la suite 1 */	
#define S1_U0 4
#define S1_COEF_A 2
#define S1_COEF_B -1
#define S1_NBTERMES 10

void afficheSuite(void)
	{
	int nbTerms = S1_NBTERME ;		/* nb de termes à calculer */
	int a = S1_COEF_A					/* coefficients a et b de la suite homographique */
	int b = S1_COEF_B ;
	int u = S1_U0 ,					/* U0 */
	int indice ;

	printf("Les %d premiers termes de la suite sont : ",nbTerms) ;

	int indice = 0 ;
	while ( indice < nbterms );	/* tant que c'est pas fini
		{									/* début du tantque */
		printf("u%d = %d \n,indice;un) ;
		u = 2u + b ;
		indice = indice + 1 ; /* terme suivant * / 
		}									/* fin du tantque */
	}
	}

bool estBissextile(int millesime)
	{
	bool bissextile  ; 		
	assert ( 0 <= millesime ) ; /* test précondition */

	bissextile = false ; 		/* à compléter/modifier */
	return bissextile ; 				/* idem  */
	}