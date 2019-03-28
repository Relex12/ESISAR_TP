/******************************************************************************
 * Implementation du module gestion de stock d'un magasin
 * avec une table de hachage
 ******************************************************************************/

#include "store.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <string.h>

/*----------------------------------------------------------------------------
 * Cette fonction initialise le tableau hash_table
 * en positionnant tous les elements à NULL_ITEM
 *----------------------------------------------------------------------------*/
void init(){
    int i;
    for(i=0;i<TABLE_SIZE;i++)
    {
        hash_table[i].status = NULL_ITEM;
        hash_table[i].price = 0.00f;
        hash_table[i].code = 0;
		hash_table[i].dirty = 0;
    }
}


/*----------------------------------------------------------------------------
 * Cette fonction calcule la valeur de hachage pour le produit itemCode
 *----------------------------------------------------------------------------*/
uint32_t hashkey(uint32_t itemCode,uint32_t nbTry){
    return (((itemCode%TABLE_SIZE)+nbTry*(1+itemCode%(TABLE_SIZE -1)))%TABLE_SIZE);
}

/*----------------------------------------------------------------------------
 * Cette fonction insère le produit indiqué dans la table de hachage.
 * Si le produit est inséré avec succès, alors la fonction retourne SUCCESS (0)
 * Si le produit existe déjà dans la table, alors la fonction retourne INSERT_ALREADY_EXIST (-1),
 * et la table de hachage n'est pas modifiée
 * Si la table est pleine, alors la fonction retourne TABLE_FULL (-2).
 *----------------------------------------------------------------------------*/
int insertItem(uint32_t itemCode, char* itemName, float itemPrice){
  int premierLibre = -1;
  int parcourt;
  int i = 0;
  parcourt = hashkey(itemCode,i);
  while ( (hash_table[parcourt].status != NULL_ITEM) && (i < TABLE_SIZE)  && (hash_table[parcourt].code != itemCode)) {
    i++;
    parcourt = hashkey(itemCode,i);
	if ( (premierLibre == -1) && (hash_table[parcourt].status == DELETED_ITEM) ){
		// printf("premier libre est %d\n",parcourt);
		premierLibre = parcourt;
	}
  }
  if ( (hash_table[parcourt].code == itemCode) && (hash_table[parcourt].status != DELETED_ITEM) ){
	printf(" l'element existe deja %d\n",itemCode);
	return INSERT_ALREADY_EXIST;
  }

  if (premierLibre != -1) {
    parcourt = premierLibre;
  }
   if ( (i == TABLE_SIZE) && (premierLibre == -1) ){
	printf("table pleine\n");
	return TABLE_FULL;
  }
  hash_table[parcourt].status = USED_ITEM;
  hash_table[parcourt].code = itemCode;
  hash_table[parcourt].dirty = 0;
  memcpy(hash_table[parcourt].name,itemName,strlen(itemName)+1) ;
  hash_table[parcourt].price = itemPrice;
  return SUCCESS;
}

/*----------------------------------------------------------------------------
 * fonction de suppression d'un produit du magasin
 * Si le produit est supprimé avec succès, alors la fonction retourne SUCCESS (0)
 * Si le produit n'existe pas, alors la fonction retourne DELETE_NO_ROW (-4)
 *----------------------------------------------------------------------------*/
int suppressItem(unsigned int itemCode){
  int parcourt;
  int i = 1;
  parcourt = hashkey(itemCode,0);
  while ( (hash_table[parcourt].status != NULL_ITEM) && (i < TABLE_SIZE) ) {
    if (hash_table[parcourt].code == itemCode) {
      hash_table[parcourt].status = DELETED_ITEM;
      return SUCCESS;
    }
    parcourt = hashkey(itemCode,i);
    i++;
	printf(" i = %d \n",i);
  }
  return DELETE_NO_ROW;

}

/*----------------------------------------------------------------------------
 * Pour chaque produit, cette fonction affiche sur une ligne
 * le code du produit
 * son libellé
 * son prix
 * son index dans la table de hashage
 * sa valeur de hash
 *----------------------------------------------------------------------------*/
void dumpItems(){
  printf("%-10s %-32s %-10s %-10s %-10s\n","CODE","LIBELE","PRIX","INDEX","HASH");
  for (int i = 0; i < TABLE_SIZE; i++) {
    if (hash_table[i].status == USED_ITEM) printf("%-10d %-32s %-10.2f %-10d %-10d\n",hash_table[i].code,hash_table[i].name,hash_table[i].price,i,i);
  }
}


/*----------------------------------------------------------------------------
 * Cette fonction trouve le produit dont le code est itemCode.
 * Cette fonction retourne NULL si le produit n'existe pas.
 * Cette fonction retourne un pointeur vers le produit si le produit existe.
 *----------------------------------------------------------------------------*/
Item *getItem(unsigned int itemCode){
	int i = 0;
	int parcourt;
	parcourt = hashkey(itemCode,i);
	while( (i < TABLE_SIZE) && (hash_table[parcourt].status != NULL_ITEM ) && (hash_table[parcourt].code != itemCode) ){
		i++;
		parcourt = hashkey(itemCode,i);
	}
	if( hash_table[parcourt].code == itemCode) return hash_table+parcourt;
	else return NULL;
}

/*----------------------------------------------------------------------------
 *  fonction de mise à jour d'un produit :
 * Si le produit est mis à jour avec succès, alors la fonction retourne SUCCESS (0)
 * Si le produit n'existe pas, alors la fonction retourne UPDATE_NO_ROW (-5)
 *----------------------------------------------------------------------------*/
int updateItem(unsigned int itemCode, char *itemName, float itemPrice){
  return 0;
}



/*----------------------------------------------------------------------------
 * la fonction de réorganisation in situ:
 *----------------------------------------------------------------------------*/
void rebuildTable(){
	int j = 0;
	int a;
	for(int i = 0 ; i < TABLE_SIZE ;i++ ){
		if(hash_table[i].status == DELETED_ITEM ){
			hash_table[i].status = NULL_ITEM;
			hash_table[i].dirty = 0;
		}
		else if (hash_table[i].status == USED_ITEM)hash_table[i].dirty = 1;
	}
	while(j < TABLE_SIZE){
		if(hash_table[j].dirty == 1){
			a = insertItem(hash_table[j].code,hash_table[j].name,hash_table[j].price);
			if( a != INSERT_ALREADY_EXIST){
				hash_table[j].status = NULL_ITEM;
			}
			hash_table[j].dirty = 0;
			j = 0;
		}
		else j++;
	}
}
