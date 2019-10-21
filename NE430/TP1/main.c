#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include "binome6MyAlgo.h"


#define MAXLEN 100

// nous obtenons un résultat de 87.78 % de réponses correctes
// avec la commande : ./main routes iptest.result


// This function must not be modified !!!
int loadFile(char *path)
{
	FILE *fi;
	char s[MAXLEN],*p,*start;
 	struct in_addr c;
	unsigned int addr,netmask,gw;

	// first sanity check
	if (!path) return 0;
	if ((fi=fopen(path,"r")) == NULL ) return 0;

	// read file line by line (max = MAXLEN )
	while (fgets(s,MAXLEN,fi) != NULL) {
		s[MAXLEN]=0;
		p=start=s;
		// seek for blank char
		while (*p && (*p != ' ')) p++;
		if (p > start) {
			*p=0; p++;
			if (inet_aton(start,&c) == 0 ) continue;
			addr=htonl(c.s_addr);
		}
		// skip remaining blank char
		while (*p && (*p == ' ')) p++;

		// stat a new search for blank char
		start=p;
		while (*p && (*p != ' ')) p++;
		if (p > start) {
			*p=0; p++;
			if (inet_aton(start,&c) == 0 ) continue;
			netmask=htonl(c.s_addr);
		}
		// skip remaining blank char
		while (*p && (*p == ' ')) p++;

		// stat a new search for blank '\n' char
		start=p;
		while (*p && (*p != '\n')) p++;
		if (p > start) {
			*p=0; p++;
			if (inet_aton(start,&c) == 0 ) continue;
			gw=htonl(c.s_addr);
		}

		// call your function to insert entry to routing table
		insertMyAlgo(addr,netmask,gw);
    // getchar();
	}
	fclose(fi);
	return 1;
}


void testTout(char *path) {
	FILE *fi;
	char s[MAXLEN],*p,*start;
 	struct in_addr c;
	unsigned int addr,result;


	int total = 0;
	int total_ok = 0;

	// first sanity check
	if (!path) return;
	if ((fi=fopen(path,"r")) == NULL ) return;

	// read file line by line (max = MAXLEN )
	while (fgets(s,MAXLEN,fi) != NULL) {
		s[MAXLEN]=0;
		p=start=s;
		// seek for blank char
		while (*p && (*p != ' ')) p++;
		if (p > start) {
			*p=0; p++;
			if (inet_aton(start,&c) == 0 ) continue;
			addr=htonl(c.s_addr);
		}
		// skip remaining blank char
		while (*p && (*p == ' ')) p++;

		// stat a new search for blank char
		start=p;
		while (*p && (*p != ' ')) p++;
		if (p > start) {
			*p=0; p++;
			if (inet_aton(start,&c) == 0 ) continue;
			result=htonl(c.s_addr);
		}

		if(lookupMyAlgo(addr) == result) total_ok++;
//		else printf("la %d est fausse : %u\n",total,addr);
		total++;
	}
	fclose(fi);

	printf("Total testé = %d\n", total);
	printf("Total ok    = %d\n", total_ok);
	printf("%f%%ok\n", (float) 100*total_ok/total);
}


// only for debug purpose might be modified !
int main (int argc,char *argv[]) {
	char s[MAXLEN];
	int addr;
 	struct in_addr a;

	initMyAlgo();
	if ((argc > 1 ) && (loadFile(argv[1]))) {
		if(argc > 2 ) {
			testTout(argv[2]);
		}

		else {
			while (1) {
				printf("IP : ");
				fgets(s,MAXLEN,stdin);
				s[MAXLEN]=0;
				if (inet_aton(s,&a) == 0 ) continue;
				addr=htonl(a.s_addr);
				a.s_addr=htonl(lookupMyAlgo(addr));
				printf("GW found = %s\n",inet_ntoa(a));
			}
		}
	}

	return 0;
}
