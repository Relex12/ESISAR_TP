#include <stdio.h> 
#include <stdlib.h>
#include <strings.h> 
#include <string.h> 
#include <unistd.h> 
#include "AlgoGenetique.h" 


#define lire(gene,i)    (i%2)?(gene[i/2]&0xF):(gene[i/2]>>4); 

/*
void affiche(unsigned char *gene)
{
//	char code[]="+-*//*"; 
	int i=0,res;  
	// the last gene is useless 
	while (i<(NBGENE-1)) {
		res=lire(gene,i); 
		if (i%2)
			printf("%c ",code[res%4]); 
		else 
			printf("0x%x ",res);	
		i=i+1; 
	}
	printf("\n"); 
}
*/



int conversion_nb (int i, unsigned char *gene) {
	int res = lire(gene,i);
	if (res == 'a')
		res = 10;
	else if (res == 'b')
		res = 11;
	else if (res == 'c')
		res = 12;
	else if (res == 'd')
		res = 13;
	else if (res == 'e')
		res = 14;
	else if (res == 'f')
		res = 15;
	else 
		res = res;
	return res; }

int conversion_op (int i, unsigned char *gene)  {
	int res = lire (gene,i);
	if (res==0 || res==4 || res==8 || res=='c')
		res = 0;
	if (res==1 || res==5 || res==9 || res=='d')
		res = 1;
	if (res==2 || res==6 || res=='a' || res=='e')
		res = 2;
	if (res==3 || res==7 || res=='b' || res=='f')
		res = 3;
	return res; }
	
		
void calcul (serpent *g) {
	int i = 0;
	int j = 0;
	int gen[NBGENE-1];
printf("test 2 accompli\n");
	while (i<(NBGENE-1)) { 
		if (i%4 > 1) {
			if (i%2 == 1)
				gen[j] = conversion_op(i, g-> gene);
			else
				gen[j] = conversion_nb(i, g-> gene);
			j++;
			}
		i++;
		}
printf("test 3 accompli\n");

	i = j = 0;
	int taille_tab = NBGENE - 1;
	while ( i < NBGENE-1) {		// gestion des multiplications
		if (i % 2 == 1 &&  gen[i] == 2) {		
			gen[i-1] = gen [i-1] * gen [i+1];
			for (j=0; j < (NBGENE - i -2); j++)  // si out of range mettre -1 à la place de -2
				gen[i + j] = gen[i + j + 2] ;
			gen[NBGENE-2]  = gen[NBGENE-1] = 0; 
			taille_tab =  taille_tab -2;
			j = 0;
			}

		else if (i % 2 == 1 &&  gen[i] == 3) { 		// gestion des divisions
printf("test 4 accompli\n");
			if (gen[i+1]  == 0) { // si division pa zéro
				gen[0] = MAX;
				for (j = 0; j < NBGENE -2; j++)
					gen[j + 1] = 0 ;
				taille_tab =  1;
				j = 0;
				}
			else {
				gen[i-1] = gen [i-1] / gen [i+1];
				for (j=0; j < (NBGENE - i -2); j++)  // si out of range mettre -1 à la place de -2
					gen[i + j] = gen[i + j + 2] ;
				gen[NBGENE-2]  = gen[NBGENE-1] = 0; 
				taille_tab =  taille_tab -2;
				j = 0;
				}
			}
		i++;
		}
printf("test 5 accompli\n");

	while ( taille_tab > 1) {		// gestion des additions et des soustractions
		if (i % 2 == 1) {
			if  (gen[i] == 0) 		// si c'est une addition
				gen[i-1] = gen [i-1] + gen [i+1];
			else 				// si c'est une soustraction
				gen[i-1] = gen [i-1] - gen [i+1];
			for (j=0; j < (NBGENE - i -2); j++)  // si out of range mettre -1 à la place de -2
				gen[i + j] = gen[i + j + 2] ;
			gen[NBGENE-2]  = gen[NBGENE-1] = 0; 
			taille_tab =  taille_tab -2;
			j = 0;
			}
		i++;
		}
printf("test 6 accompli\n");
	// il faut trouver un moyen de renvoyer le score du serpent
	}
		

int main()  // à la base c'était pas un main ça
{
printf("test 1 accompli\n");
int i,expect; 
serpent test[]={
	{"\x67\xc6\x69\x73\x51\xff\x4a\xec\x29\xcd\xba\xab\xf2\xfb\xe3\x46\x7c\xc2\x54\xf8\x1b\xe8\xe7\x8d\x76\x5a\x2e\x63\x33\x9f\xc9\x9a",660},
	{"\x66\x32\x0d\xb7\x31\x58\xa3\x5a\x25\x5d\x05\x17\x58\xe9\x5e\xd4\xab\xb2\xcd\xc6\x9b\xb4\x54\x11\x0e\x82\x74\x41\x21\x3d\xdc\x87",735},
	{"\x70\xe9\x3e\xa1\x41\xe1\xfc\x67\x3e\x01\x7e\x97\xea\xdc\x6b\x96\x8f\x38\x5c\x2a\xec\xb0\x3b\xfb\x32\xaf\x3c\x54\xec\x18\xdb\x5c",694},
	{"\x02\x1a\xfe\x43\xfb\xfa\xaa\x3a\xfb\x29\xd1\xe6\x05\x3c\x7c\x94\x75\xd8\xbe\x61\x89\xf9\x5c\xbb\xa8\x99\x0f\x95\xb1\xeb\xf1\xb3",646},
	{"\x05\xef\xf7\x00\xe9\xa1\x3a\xe5\xca\x0b\xcb\xd0\x48\x47\x64\xbd\x1f\x23\x1e\xa8\x1c\x7b\x64\xc5\x14\x73\x5a\xc5\x5e\x4b\x79\x63",MAX},
	{"\x3b\x70\x64\x24\x11\x9e\x09\xdc\xaa\xd4\xac\xf2\x1b\x10\xaf\x3b\x33\xcd\xe3\x50\x48\x47\x15\x5c\xbb\x6f\x22\x19\xba\x9b\x7d\xf5",543},
	{"\x0b\xe1\x1a\x1c\x7f\x23\xf8\x29\xf8\xa4\x1b\x13\xb5\xca\x4e\xe8\x98\x32\x38\xe0\x79\x4d\x3d\x34\xbc\x5f\x4e\x77\xfa\xcb\x6c\x05",1302},
	{"\xac\x86\x21\x2b\xaa\x1a\x55\xa2\xbe\x70\xb5\x73\x3b\x04\x5c\xd3\x36\x94\xb3\xaf\xe2\xf0\xe4\x9e\x4f\x32\x15\x49\xfd\x82\x4e\xa9",MAX},
	{"\x08\x70\xd4\xb2\x8a\x29\x54\x48\x9a\x0a\xbc\xd5\x0e\x18\xa8\x44\xac\x5b\xf3\x8e\x4c\xd7\x2d\x9b\x09\x42\xe5\x06\xc4\x33\xaf\xcd",MAX},
	{"\xa3\x84\x7f\x2d\xad\xd4\x76\x47\xde\x32\x1c\xec\x4a\xc4\x30\xf6\x20\x23\x85\x6c\xfb\xb2\x07\x04\xf4\xec\x0b\xb9\x20\xba\x86\xc3",MAX},
	{"\x3e\x05\xf1\xec\xd9\x67\x33\xb7\x99\x50\xa3\xe3\x14\xd3\xd9\x34\xf7\x5e\xa0\xf2\x10\xa8\xf6\x05\x94\x01\xbe\xb4\xbc\x44\x78\xfa",727}
	}; 

	for(i=0;i<sizeof(test)/sizeof(serpent);i++) {
		expect=test[i].score; 
		calcul(&test[i]);
		if (expect != test[i].score) printf("error\n");  
	}
return 1;}
/*
void selection(groupe *population,groupe *parents)
{
}

int evaluation(groupe *population) 
{
}

void generationAleatoire(groupe *population)
{
}

void reproduction(groupe *population,groupe *parents)
{
}
void mutation (groupe *population)
{
}



*/
