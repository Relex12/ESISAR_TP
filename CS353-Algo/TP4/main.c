/******************************************************************************
 * Programme de test du gestionnaire de magasin                               *                                                               *
 ******************************************************************************/

#include "store.h"
#include <stdio.h>
#include <string.h>


int main(){
  Result* resultat = NULL;
  char string[16] = "/Nom de l'item/";
  printf("****** Gestionnaire de magasin ******\n");
  init();
  for (int i = 0; i < TABLE_SIZE-500; i++) {
    insertItem( (uint32_t) i,string, (float) i);
  }
  insertItem( 600 , "je t ai trouve", 10);
  insertItem( 610 , "je t ai trouve", 30);
  //dumpItems();
  suppressItem(610);
  updateItem(600,"je t ai trouve",40);
  resultat = findItemWithIndex("je t ai trouve");
  if(resultat != NULL) printf("les elements trouve sont : \n");
  while(resultat != NULL){
	printf("nom : %s prix %f code %d\n",resultat->item->name,resultat->item->price,resultat->item->code);
	resultat = resultat->next;
  }
  printf("====== Gestionnaire de magasin ======\n");
  return 0;
}
