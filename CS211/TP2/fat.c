#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>




#define BLOCSIZE 512
#define BLOCNUM 1024
#define NAMELEN 256

struct objet
{
char nom[NAMELEN];
unsigned int taille;
unsigned short auteur;
unsigned short index;
struct objet *next;
};

struct objet *obj  ;
char volume[BLOCSIZE * BLOCNUM ];
unsigned short FAT[BLOCNUM];
unsigned short freeblocks;



void initialise_fat()
{
freeblocks = BLOCNUM;
obj -> next = NULL;
for (int i = 0; i < BLOCNUM; i++)
  FAT[i] = 0xfffe;
}



struct objet *rechercher_objet(char *nom){
  struct objet * temp = obj;
  while (temp != NULL) {
      if (temp -> nom == nom)
        return temp;
      else temp = temp -> next;
    }
    printf ("aucun objet de la structure ne contient ce champs");
    return NULL;
    }




// fonction qui permet de trouver le prochain bloc libre dans FAT
int prochain_libre() {
	for(int i = 0; i < BLOCNUM; ++i)
		if(FAT[i] == 0xffff)
			return i;

	return -1;
}




struct objet *creer_objet(char *nom, unsigned short auteur,unsigned int taille, char *data){
  if (rechercher_objet(nom) ==  NULL) {
    if (taille < freeblocks * BLOCSIZE) {

      struct objet *nouveau = obj;
      if (obj == NULL)
        nouveau = malloc(sizeof(struct objet));
      else {
        while (nouveau -> next != NULL)
          nouveau = nouveau -> next;
        nouveau = malloc(sizeof(struct objet));
        }
//    nouveau -> nom = nom;
      nouveau -> auteur = auteur;
      nouveau -> taille = taille;
      nouveau -> next = NULL;
      nouveau -> index = -1;

      int nb_bloc = taille / BLOCSIZE;
      if (taille%BLOCSIZE != 0)
        nb_bloc++;

      int identifiant, next_id;
      for (int i = 0; i < nb_bloc; i ++) {
          next_id = prochain_libre();
          freeblocks --;
          if (i == 0)
            nouveau -> index = next_id;
          else
            FAT[identifiant] = next_id;
          if (BLOCSIZE < taille - identifiant * BLOCSIZE)
            memcpy(&volume[identifiant * BLOCSIZE], &data[identifiant * BLOCSIZE], BLOCSIZE);
          else
            memcpy(&volume[identifiant * BLOCSIZE], &data[identifiant * BLOCSIZE], (taille - identifiant * BLOCSIZE));

          identifiant = next_id;
        }
        FAT[identifiant] = 0xfffe;
        return nouveau;
      }
    else {
      printf("la taille que vous demandez est trop importante");
      return NULL;
    }
}
  else {
    printf ("nom de domaine déjà utilisé dans un aute objet de la structure");
    return NULL;
    }

}





int supprimer_objet(char *nom){
  if (rechercher_objet(nom) ==  NULL)
    return -1;
  else {
    struct objet * temp =  rechercher_objet(nom);
    unsigned short next_index = temp->index;
    unsigned short suppr;

    do {
  		suppr = next_index;
  		freeblocks++;
      next_index = FAT[suppr];
      FAT[suppr] = 0xffff;
    } while(next_index != 0xfffe);

    struct objet * temp2;

    	if (temp2 == obj) {
    		obj = temp2 -> next;
    		free(temp2);
    	 }
      else {
    		while(temp2 -> next != temp) {
    			temp2 = temp2 -> next;
    		}
    		temp2 -> next = temp2 -> next -> next;
    		free(temp);
    	}


    return 0;
  }
}



void supprimer_tout(){
  initialise_fat();
  }



int main(int argc, char const *argv[]) {
  printf ("TP de Bonnet Adrian et Bec-Lucat Romain\n");
  return 0;
}
