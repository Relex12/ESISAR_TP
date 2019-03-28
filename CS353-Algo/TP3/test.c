/******************************************************************************
 * Programme de test du gestionnaire de magasin                               *                                                               *
 ******************************************************************************/

#include "store.h"
#include <stdio.h>
#include <string.h>


int main(){
    char string[13] = "Nom de l'item";
    printf("****** Gestionnaire de magasin ******\n");
    init();
    for (int i = 0; i < TABLE_SIZE; i++) {
      insertItem( (uint32_t) i,string, (float) i);
    }
    dumpItems();
	printf("la\n");
    for (int i = 0; i < TABLE_SIZE; i=i+3){
      suppressItem(i);
    }
	printf("post suppression\n");
	for (int i = TABLE_SIZE; i < TABLE_SIZE*2; i++) {
      insertItem( (uint32_t) i,string, (float) i);
    }
	rebuildTable();
   	dumpItems();
    printf("====== Gestionnaire de magasin ======\n");
    return 0;
}
