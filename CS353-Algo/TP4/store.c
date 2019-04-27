/******************************************************************************
 * Implementation du module gestion de stock d'un magasin
 * avec une table de hachage
 ******************************************************************************/

#include "store.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*----------------------------------------------------------------------------
 * Cette fonction initialise le tableau hash_table
 * en positionnant tous les elements à NULL_ITEM
 *----------------------------------------------------------------------------*/
void init()
{
    int i;
    for(i=0;i<TABLE_SIZE;i++)
    {
        hash_table[i].status = NULL_ITEM;
        hash_table[i].code = -1;
        hash_table[i].price = 0.00;
        hash_table_index[i].status = NULL_ITEM;
        hash_table_index[i].item = NULL;
    }
}


/*----------------------------------------------------------------------------
 * Cette fonction calcule la valeur de hachage pour le produit itemCode
 *----------------------------------------------------------------------------*/
uint32_t hashkey(uint32_t itemCode,uint32_t nbTry)
{
    return (((itemCode%TABLE_SIZE)+nbTry*(1+itemCode%(TABLE_SIZE -1)))%TABLE_SIZE);
}
//

uint32_t hashIndex(char *buffer, int size)
{
	uint32_t h = 0;
	for (int i=0; i<size; i++)
	{
		h = ( h * 1103515245u ) + 12345u + (unsigned char)buffer[i];
	}
	return h;
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
  //////////////////////////////////hash_table
  parcourt = hashkey(itemCode,i);
  while ( (hash_table[parcourt].status != NULL_ITEM) && (i < TABLE_SIZE)  && (hash_table[parcourt].code != itemCode)) {
    i++;
    parcourt = hashkey(itemCode,i);
	if ( (premierLibre == -1) && (hash_table[parcourt].status == DELETED_ITEM) ){
		premierLibre = parcourt;
	}
  }
  if ( (hash_table[parcourt].code == itemCode) && (hash_table[parcourt].status != DELETED_ITEM) ){
	  printf(" l'element existe deja dans hash_table %d\n",itemCode);
	  return INSERT_ALREADY_EXIST;
  }
  if (premierLibre != -1) {
    parcourt = premierLibre;
  }
  
  if ( (i == TABLE_SIZE) && (premierLibre == -1) ){
	printf("table pleine hash_table\n");
	return TABLE_FULL;
  }
  /////////////////////////////////hash_table_index
  int premierLibreIndex = -1;
  int parcourtindex;
  int indexhash;
  int j = 0;
  
  indexhash = hashIndex(itemName,strlen(itemName));
  parcourtindex = hashkey(indexhash,j);
  
  while ( (hash_table_index[parcourtindex].status != NULL_ITEM) && (j < TABLE_SIZE)  && hash_table_index[parcourtindex].item != NULL && hash_table_index[parcourtindex].item->code != itemCode ){
    j++;
    parcourtindex = hashkey(indexhash,j);
    if ( (premierLibreIndex == -1) && (hash_table_index[parcourtindex].status == DELETED_ITEM) ){
      premierLibreIndex = parcourtindex;
    }
  }
  
  if ( hash_table_index[parcourtindex].item != NULL && ((hash_table_index[parcourtindex].item->code == itemCode) && (hash_table_index[parcourtindex].status != DELETED_ITEM)) ){
    printf(" l'element existe deja dans hash_table_index %d\n",itemCode);
    return INSERT_ALREADY_EXIST;
  }

  if (premierLibreIndex != -1) {
    parcourtindex = premierLibreIndex;
  }
  if ( (j >= TABLE_SIZE) && (premierLibreIndex == -1) ){
	  printf("table pleine hash_table_index\n");
	  return TABLE_FULL;
  }
  ////////////////////////////////mise a jours des tables
  hash_table[parcourt].status = USED_ITEM;
  hash_table[parcourt].code = itemCode;
  hash_table[parcourt].dirty = 0;
  memcpy(hash_table[parcourt].name,itemName,strlen(itemName)+1) ;
  hash_table[parcourt].price = itemPrice;
  hash_table_index[parcourtindex].item = &hash_table[parcourt];
  hash_table_index[parcourtindex].status = USED_ITEM;
  return SUCCESS;
}

/*----------------------------------------------------------------------------
 * fonction de suppression d'un produit du magasin
 * Si le produit est supprimé avec succès, alors la fonction retourne SUCCESS (0)
 * Si le produit n'existe pas, alors la fonction retourne DELETE_NO_ROW (-4)
 *----------------------------------------------------------------------------*/
int suppressItem(uint32_t itemCode){
  int parcourt,parcourtindex;
  int hashindex;
  int i = 0,j =0;
  parcourt = hashkey(itemCode,0);
  while ( (hash_table[parcourt].status != NULL_ITEM) && (i < TABLE_SIZE) ) {
    if (hash_table[parcourt].code == itemCode) {
      hashindex = hashIndex(hash_table[parcourt].name,strlen(hash_table[parcourt].name));
      parcourtindex = hashkey(hashindex,j);
      while ((hash_table_index[parcourtindex].status != NULL_ITEM) && (j < TABLE_SIZE)) {
          if (hash_table_index[parcourtindex].item == (hash_table+parcourt) ) {
            hash_table_index[parcourtindex].status = DELETED_ITEM;
            hash_table[parcourt].status = DELETED_ITEM;
            return SUCCESS;
          }
        j++;
        parcourtindex = hashkey(hashindex,j);
      }
    }
    i++;
    parcourt = hashkey(itemCode,i);
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
 *  fonction de mise à jour d'un produit :
 * Si le produit est mis à jour avec succès, alors la fonction retourne SUCCESS (0)
 * Si le produit n'existe pas, alors la fonction retourne UPDATE_NO_ROW (-5)
 *----------------------------------------------------------------------------*/
int updateItem(uint32_t itemCode, char *itemName, float itemPrice){
	
  Item* itemMod;
  
	if( ( itemMod = findItem2(itemCode) ) == NULL ){
	  return UPDATE_NO_ROW;
	}
	if(strcmp(itemName,itemMod->name) == 0){
		itemMod->price = itemPrice;
		return SUCCESS;
	}
	else{
		suppressItem(itemCode);
		insertItem(itemCode,itemName,itemPrice);
		return SUCCESS;
	}
	return UPDATE_NO_ROW;
}


/*----------------------------------------------------------------------------
 * Fonction simple de recherche des produits par libellé :
 *
 * Cette fonction retourne une liste chaineeavec tous les produits dont le libellé est égal à itemName.
 * Exemple : si il y a trois produits 1 - ḋ Sel Ṡ , 2 - ḋ SelṠ et 3-ḋ Confiture Ṡ, alors
 * findItem(ḋ Sel Ṡ)
 * retourne les deux produits 1-ḋ Sel Ṡ et 2-ḋ Sel Ṡ.
 *----------------------------------------------------------------------------*/
Item* findItem2(int itemCode){
	int i = 0;
	int parcourt;
	parcourt = hashkey(itemCode,i);
	while( (i < TABLE_SIZE) && (hash_table[parcourt].status != NULL_ITEM ) && (hash_table[parcourt].code != itemCode) ){
		i++;
		parcourt = hashkey(itemCode,i);
	}
	if( hash_table[parcourt].code == itemCode) return &hash_table[parcourt];
	else return NULL;
}


/*----------------------------------------------------------------------------
 * Fonction de recherche des produits par libellé avec index
 *----------------------------------------------------------------------------*/

Result* findItemWithIndex(char* itemName){
  int hashindex = hashIndex(itemName,strlen(itemName));
  int i = 0;
  Result* table = NULL;
  Result* table_index = NULL;
  int hash = hashkey(hashindex,i);
  while ( i < TABLE_SIZE && hash_table_index[hash].status != NULL_ITEM) {
    if(strcmp(hash_table_index[hash].item->name,itemName) == 0 && hash_table_index[hash].item->status == USED_ITEM){
      if( ( table = malloc(sizeof(table)) ) == NULL ){
        printf("La mémoire est pleine, erreur dans find item with index\n");
        return NULL;
      }
	  table->item = hash_table_index[hash].item;
	  table->next = table_index;
	  table_index = table;
    }
    i++;
    hash = hashkey(hashindex,i);
  }
  return table;
}

int suppressItemIndex(uint32_t itemCode,Item *item){
  printf("Fait dans supressItem\n");
  return 0;
}

int insertItemIndex(uint32_t itemCode,Item *item){
  printf("Fait dans insertItem\n");
  return 0;
}
