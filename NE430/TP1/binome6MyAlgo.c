#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

#include "binome6MyAlgo.h"

// nous obtenons un résultat de 87.78 % de réponses correctes
// avec la commande : ./main routes iptest.result


void initMyAlgo(){}

void insertMyAlgo(unsigned int addr,unsigned int netmask,unsigned int gw){
  unsigned int dec = 29;
  unsigned int taille = 0;
  Node* target = arbre;
  //printf("-----------------\naddr %u\n",addr);
  while (((netmask >> dec & (0x7)) == 0x7) && (dec > 0)) {        // on parcourt l'abre jusqu'à ne plus avoir de paquet 111
    for (unsigned int i = 0; i < 8; i++) {
      if ( ( (addr >> dec) & (0x7) ) == i) {
        //printf("on trouve %u avec dec : %d \n",(addr >> dec) & (0x7),dec);
        if (target == NULL && target != arbre) {

          if ( (target = malloc(sizeof(Node)) ) == NULL) {
            //printf("erreur\n");
            exit(0);
          }
          for (int j = 0; j < 8; j++) {
            target->f[j] = NULL;
          }
        }
        else if (target == NULL && target == arbre) {
          if ( (arbre = malloc(sizeof(Node)) ) == NULL) {
            //printf("erreur\n");
            exit(0);
          }
          for (int j = 0; j < 8; j++) {
            arbre->f[j] = NULL;
          }
          target = arbre;
        }

        if (target->f[i] == NULL) {
          if ( (target->f[i] = malloc(sizeof(Node)) ) == NULL) {
            //printf("erreur\n");
            exit(0);
          }
          //printf("on malloc f%d\n",i);
          for (int j = 0; j < 8; j++) {
            (target->f[i])->f[j] = NULL;
          }
          //printf("---on a mis les fils a null\n");
        }

        //printf("on va dans f%d\n",i);
        ////printf("%p target\n",target);
        target = target->f[i];
        target->mask_size = 0;
      }
    }
    taille +=3;
    dec -= 3;
  }

  if (dec < 0) {                                                    // on a atteint les deux derniers bits de netmask
    dec = 0;
  }
  //on a soit ''... 111 '000' 000 ...'' soit '110' soit '100' dans net mask
  if( ((netmask >> dec) & (0x7)) == 0 && target->mask_size < taille){ //000 1 noeud
	//printf("---- on a un noeud a remplir ----\n");
    target->gw = gw;  //on a qu'un noeud a metre
    target->mask_size = taille;
	if(taille == 0) printf("on a taille = 0\n");
	//printf("on met %u\n",gw);
  }

  if( ((netmask >> dec & (0x7))) == (0x6)){ //110 2 noeuds
  //printf("---- on a 2 noeud a remplir ---- et on a %d\n",(addr >> dec) & (0x4));
    for (unsigned int i = 0; i < 8; i++) {
		//printf("--%d fils--\n",i);
      if ((addr >> dec & (0x6)) == ( i & (0x6) )) {
        if (target->f[i] == NULL) {
			//printf("on doit créer un fils\n");
          if ( (target->f[i] = malloc(sizeof(Node)) ) == NULL) {
            //printf("erreur\n");
            exit(0);
          }
          //printf("on malloc f[%d]\n",i);
          for (int j = 0; j < 8; j++) {
            (target->f[i])->f[j] = NULL;
          }
          //printf("---on a mis les fils a null\n");
        }
        if (target->f[i]->mask_size < (taille+2) ) { //on verifie si la taille du mask est plus petit que la taille du mask precedent
          target->f[i]->gw = gw;
			if(taille == 0) printf("on a taille = 0\n");
          target->f[i]->mask_size = taille+2;
		  //printf("on met %u dans %d\n",gw,i);
        }
      }
    }
  }

  if( (netmask >> dec & (0x7)) == (0x4)){ //100 4 noeuds
	//printf("---- on a 4 noeud a remplir ---- et on a %d\n",(addr >> dec) & (0x4));
    for (int i = 0; i < 8; i++) {
		//printf("--%d fils--\n",i);
      if (((addr >> dec) & (0x4)) == ( i & (0x4) )) {

        if (target->f[i]== NULL) {
			//printf("on doit créer un fils\n");
          if ( (target->f[i] = malloc(sizeof(Node)) ) == NULL) {
            //printf("erreur\n");
            exit(0);
          }
          //printf("on malloc f%d\n",i);
          for (int j = 0; j < 8; j++) {
            (target->f[i])->f[j] = NULL;
          }
          //printf("---on a mis les fils a null\n");
        }

        if (target->f[i]->mask_size < (taille+1)) { //on verifie si la taille du mask est plus petit que la taille du mask precedent
          target->f[i]->gw = gw;
			if(taille == 0) printf("on a taille = 0\n");
          target->f[i]->mask_size = taille+4;
		  //printf("on met %u dans %d\n",gw,i);
        }

      }
    }
  }
}


unsigned int lookupMyAlgo(unsigned int addr)
{
  Node* current_node = arbre;
  int indice;
  unsigned int gwprec = 0;
  for (int i = 0; i < 10; i ++)                   // 32 / 3 =  10.67 ; nous allons faire 10 tours de boucle classiques 0 à 9, et 1 tour bonus si i == 9
  {
    if (i != 9)
	{
      indice = 32 - 3*(i+1);                      // formule pour se placer au bon endroit dans l'adresse
      for (int j = 0; j <= 8; j ++)
      {
	  //printf("i = %d\tj = %d\tresultat = %d\n", i, j, (addr >> indice ) & 0x7);
        if (((addr >> indice ) & 0x7) == j)         // on choisi l'un des fils de current_node
		{
          if (current_node->f[j] == NULL)          // si ce fils n'existe pas, on a trouvé une feuille, on retourne la GW
			{
				if(current_node->gw != 0){
					//printf("on a trouve une gw sans pred ----\n");
					return  current_node->gw;
				}
				else{
					//printf("on prend un pred\n");
					return gwprec;
				}
			//printf("fils non existant, on retourne\n");
			}
          else									   // sinon, on incrémente i, et on continue à chercher
		{
			if(current_node->gw != 0) {
				//printf("mise a jour du pred avec %u\n",current_node->gw );
				gwprec = current_node->gw;
			}
			current_node = current_node->f[j];
			//printf("fils existant, on contine\n");
		}
          break;
        }
        if (j == 8)                               // si j == 8, ça veut dire qu'on n'a pas trouvé de fils avec un bon modulo (donc tout est faux, c'est une erreur critique)
        {
          //printf ("ici j = 8\n");
          return (-1);
        }
      }
    }
    else                    		               // si i == 9, on va chercher le fils à la mail
	{
      for (int j = 0; j < 4; j ++)
        if (addr % 4 == j)
        {
          if (current_node->f[j] == NULL)          // si ce fils n'existe pas, on a trouvé une feuille, on retourne la GW
            if(current_node->gw != 0){
				//printf("on a trouve une gw sans pred ******\n");
				return  current_node->gw;
			}
			else{
				printf("on prend le pred");
				return gwprec;
			}
          else{
			  if(current_node->gw != 0){
				  //printf("mise a jour du pred avec %u",current_node->gw);
				  gwprec = current_node->gw;
			  }
            current_node = current_node->f[j];     // sinon, on incrémente i, et on continue à chercher
		  }
          break;
        }
    }
  }
  //printf ("on retourne -1\n");
  return -1;
}
