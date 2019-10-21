// Do not RECOMPILE

#include<stdio.h>
#include<string.h>

char *valide = "exo valide\0";

void valide_ex(char *buffer){

	if(strncmp(buffer, valide, strlen(valide)) == 0)
		printf("Overflow, go to the next exercise\n");	

}

void vuln(char *buffer){

	char buf[16];
	strcpy(buf, buffer);
	printf("Return... \n");
}

int main(int argc, char **argv){

	if(argc<2)
		printf("No args\n");
	else
		vuln(argv[1]);

	printf("End of program!\n");

return 0;
}
