/******************************************************************************
 * Fichier d'entete du module gestion de stock d'un magasin
 * avec une table de hachage
 ******************************************************************************/

#include <stdbool.h>
#include <stdint.h>


/*----------------------------------------------------------------------------
 * Parametres globaux
 *----------------------------------------------------------------------------*/
#define TABLE_SIZE            1009
#define NULL_ITEM             4
#define DELETED_ITEM          2
#define USED_ITEM             1
#define ITEM_NAME_SIZE        32

/*----------------------------------------------------------------------------
 * Definition des constantes pour les retours des fonctions
 *----------------------------------------------------------------------------*/
#define SUCCESS                 0
#define INSERT_ALREADY_EXIST   -1
#define TABLE_FULL             -2
#define SELECT_NO_ROW          -3
#define DELETE_NO_ROW          -4
#define UPDATE_NO_ROW          -5


/*----------------------------------------------------------------------------
 * Definition de la structure d'un produit
 * Chaque produit est identifié par 3 champs :
 *     - son code sur 5 chiffres
 *     - son libellé
 *     - son prix en euros
 *
 *----------------------------------------------------------------------------*/
typedef struct structItem
{
	uint8_t status;  
	uint32_t code;
	char name[ITEM_NAME_SIZE];
	float price;
	uint8_t dirty; 
} Item;

typedef struct structResult
{
	Item *item; 
	struct structResult *next; 
} Result;

typedef struct structItemIndex
{
	uint8_t status;
	Item *item; 
} ItemIndex;

/*----------------------------------------------------------------------------
 * Variable globale contenant le tableau
 *----------------------------------------------------------------------------*/
Item hash_table[TABLE_SIZE];
ItemIndex hash_table_index[TABLE_SIZE];

/*----------------------------------------------------------------------------
 * Cette fonction initialise un tableau hash_table
 *----------------------------------------------------------------------------*/
void init();


/*----------------------------------------------------------------------------
 * Cette fonction calcule la valeur de hachage pour le produit itemCode
 *----------------------------------------------------------------------------*/
uint32_t hashkey(uint32_t itemCode,unsigned int nbTry); 

/*----------------------------------------------------------------------------
 * Cette fonction insère le produit indiqué dans la table de hachage.
 * Si le produit est inséré avec succès, alors la fonction retourne SUCCESS (0)
 * Si le produit existe déjà dans la table, alors la fonction retourne INSERT_ALREADY_EXIST (-1),
 * et la table de hachage n'est pas modifiée
 * Si la table est pleine, alors la fonction retourne TABLE_FULL (-2).
 *----------------------------------------------------------------------------*/
int insertItem(uint32_t  itemCode, char* itemName, float itemPrice);

/*----------------------------------------------------------------------------
 * fonction de suppression d'un produit du magasin
 * Si le produit est supprimé avec succès, alors la fonction retourne SUCCESS (0)
 * Si le produit n'existe pas, alors la fonction retourne DELETE_NO_ROW (-4)
 *----------------------------------------------------------------------------*/
int suppressItem(uint32_t  itemCode);

/*----------------------------------------------------------------------------
 * Pour chaque produit, cette fonction affiche sur une ligne
 * le code du produit
 * son libellé
 * son prix
 * son index dans la table de hashage
 * sa valeur de hash
 *----------------------------------------------------------------------------*/
void dumpItems();


/*----------------------------------------------------------------------------
 * Cette fonction trouve le produit dont le code est itemCode.
 * Cette fonction retourne NULL si le produit n'existe pas.
 * Cette fonction retourne un pointeur vers le produit si le produit existe.
 *----------------------------------------------------------------------------*/
Item *getItem(uint32_t  itemCode);

/*----------------------------------------------------------------------------
 *  fonction de mise à jour d'un produit :
 * Si le produit est mis à jour avec succès, alors la fonction retourne SUCCESS (0)
 * Si le produit n'existe pas, alors la fonction retourne UPDATE_NO_ROW (-5)
 *----------------------------------------------------------------------------*/
int updateItem(uint32_t  itemCode, char *itemName, float itemPrice);


/*----------------------------------------------------------------------------
 * la fonction de réorganisation in situ:
 *----------------------------------------------------------------------------*/
void rebuildTable();

/*----------------------------------------------------------------------------
 * Fonction simple de recherche des produits par libellé :
 *
 * Cette fonction retourne un tableau avec tous les produits dont le libellé est égal à itemName.
 * Exemple : si il y a trois produits 1 - Sel , 2 - Sel et 3- Confiture , alors
 * findItem("Sel")
 * retourne les deux produits 1-Sel et 2-Sel.
 *----------------------------------------------------------------------------*/
Result* findItem(char* itemName);

Item* findItem2(int itemCode);

uint32_t hashIndex(char *buffer, int size); 

int insertItemIndex(uint32_t itemCode,Item *item);

int suppressItemIndex(uint32_t itemCode,Item *item); 

Result *findItemWithIndex(char* itemName);



