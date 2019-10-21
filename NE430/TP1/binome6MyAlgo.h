#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

// nous obtenons un résultat de 87.78 % de réponses correctes
// avec la commande : ./main routes iptest.result


struct node {
  struct node *f[8];
  unsigned int gw;
  unsigned int mask_size;
};typedef struct node Node;

Node *arbre;

void initMyAlgo();

void insertMyAlgo(unsigned int addr,unsigned int netmask,unsigned int gw);

unsigned int lookupMyAlgo(unsigned int addr);
