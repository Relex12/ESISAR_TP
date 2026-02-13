#include <stdlib.h>
#include <stdio.h>
#include "menuUtil.h"

/* tests pour estBissextile()  */
   static int bissextiles[] = { 2000, 2004, 1600, 2008 } ;
   static int nonBissextiles[] = { 1700, 1800, 1900, 1993,1997, 2001, 2002,2003,2005, 2006, 2007,2009 } ;

    int main(int argc, char* argv[])
   {
      int i ;
		const char * nomTest = "années bissextiles" ;
      printf("*** Test Unitaires *** \n");
      printf("-- %s --\n", nomTest);
      for ( i = 0 ; i < sizeof(bissextiles)/sizeof(int) ; i++ ){
         if ( ! estBissextile(bissextiles[i])  )
         {
            printf("-- %s test n°%d échoué --\n",nomTest,i+1);
            return EXIT_FAILURE ;
         }
         else 
            printf("-- %s test n°%d passé --\n",nomTest, i+1);
      }
   
		nomTest =  "années non bissextiles" ;
      printf("-- %s --\n", nomTest);
      for ( i = 0 ; i < sizeof(nonBissextiles)/sizeof(int) ; i++ ){
         if ( estBissextile(nonBissextiles[i])  )
         {
            printf("-- %s test n°%d échoué --\n",nomTest,i+1);
            return EXIT_FAILURE ;
         }
         else 
            printf("-- %s test n°%d passé --\n",nomTest, i+1);
      }

     printf("*** Fin des Test Unitaires *** \n");
      printf("*** Aucune erreur détectée ! *** \n");
   
       return EXIT_SUCCESS ;
   }
