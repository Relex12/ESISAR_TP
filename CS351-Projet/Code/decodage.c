#include "decodage.h"

void convertionBinaire(char * nombre,char * sortie, int taille){	//fonction convertion d'une chaine de caractère avec un chiffre décimal et qui la convertit en une chaine de caractère binaire
	int nombreAConv = 0;
	int nombreConverti[taille];
	char tmpc[taille+1];
	int tmp=0;
	int i = 0;
	int nbMAX = 0;

	if (!strcmp(nombre,"")){
		strcpy(sortie,"00000");
	}
	else{
		for (int i =1; i<taille+1;i++){
			nbMAX+=pow(2,i-1);
		}
		nbMAX-=2;

		nombreAConv = atoi (nombre);

		for (int i = 0; i<taille+1;i++){
			nombreConverti[i]=0;
		}

		if (nombreAConv >nbMAX){
			printf("nombre trop grand\n");
		}
		else{
			while (i<taille+1 && nombreAConv !=0){
				nombreConverti[i]=nombreAConv%2;
				nombreAConv/=2;
				i++;
			}

			for (int i = 0; i<taille/2+1; i++){
				tmp=nombreConverti[i];
				nombreConverti[i]=nombreConverti[taille-i];
				nombreConverti[taille-i]=tmp;
			}

			for (int i = 1; i<taille+1;i++){
				sprintf(tmpc,"%d",nombreConverti[i]);
				strcpy(sortie+i-1,tmpc);
			}
		}
	}


}
int conversionDecimal(char * entree, int taille){	//convertit une chaine binaire en une nombre décimal
	int sortie=0;

	for(int i = 0; i<taille;i++){
		if (entree[i]=='1'){
			sortie+=pow(2,taille-i-1);
		}
	}

	return sortie;
}

void decodage(char * fentree, char * fsortie){
	FILE* entree = NULL;
	FILE* sortie = NULL;
	char ligne[20];
	char caract;
	char opcode[5];
	char op1[6];
	char op2[6];
	char op3[6];
	char op1T[17];
	char op2T[17];
	char op3T[17];
	char tmp[17];
	char ligneTrad[33];
	int i =0;
	int j = 0;
	int indice = 0;
	int ligneHex1 = 0;
	int ligneHex2 = 0;
	int ligneHex3 = 0;
	int ligneHex4 = 0;
	int ligneHex5 = 0;
	int ligneHex6 = 0;
	int ligneHex7 = 0;
	int ligneHex8 = 0;


//-------------OUVERTURE FICHIERS----------------
	while ( entree == NULL && sortie == NULL){
		entree = fopen(fentree,"r+");
		sortie = fopen(fsortie,"w+");
	}

//------------LECTURE ET TRI LIGNE PAR LIGNE--------
	while((caract=fscanf(entree,"%c",&caract))!=EOF){	// test fin de fichier
		fseek(entree,-1,SEEK_CUR);
		fgets(ligne,20,entree);			//on récupère une ligne

		while (ligne[i] != '\0' && ligne[i]!=' ' && ligne[i]!='\n'){		//tri de la ligne par type d'objet
			opcode[j] = ligne[i];												// définition de l'opcode: tant qu'on ne rencontre pas un espace, on copie la ligne dans la chaine opcode
			i++;
			j++;
		}
		opcode[j]='\0';																//fin de chaine
		j = 0;
		i++;
		while (ligne[i]!=',' && i<strlen(ligne) && ligne[i]!='\n'){			//definition opérande 1: détection virgule ou fin de chaine
				op1[j] = ligne[i];
				i++;
				j++;
		}
		op1[j]='\0';
		j=0;
		i++;
	 	while (ligne[i]!= ',' && ligne[i]!='\n' && i<strlen(ligne)){		//définition opérande 2:détection virgule ou fin de chaine
				op2[j] = ligne[i];
				i++;j++;
		}
		op2[j]='\0';
		j=0;
		i++;
		while (i<strlen(ligne) && ligne[i]!='\n'){											//définition opérande 3:détection fin de chaine
			op3[j] = ligne[i];
			i++;j++;
		}
		op3[j]='\0';
		j=0;
		i=0;

		if(!strcmp(opcode,"LW") || !strcmp(opcode,"SW")){
			memmove(op3,strchr(op2,'(')+1,5);
			op3[strlen(op3)-1]='\0';

			while(i<strlen(op2) && op2[i] != '('){
				op2[i]=op2[i];
				i++;
			}
			op2[i] = '\0';
		}
		//--------------CONVERSION EN BINAIRE------------------


		if(strchr(op1,'$') != NULL){
			convertionBinaire(memmove(tmp,op1+1,5),op1T,5);	//conversion en binaire
		}
		else{
			convertionBinaire(op1,op1T,16);
		}
		if(strchr(op2,'$') != NULL){
			convertionBinaire(memmove(tmp,op2+1,5),op2T,5);	//conversion char to int
		}
		else
		{
			convertionBinaire(op2,op2T,16);
		}
		if(strchr(op3,'$') != NULL){
			convertionBinaire(memmove(tmp,op3+1,5),op3T,5);	//conversion char to int
		}
		else{
			convertionBinaire(op3,op3T,16);
		}

//------------------------DETERMINER LE TYPE D'INSTRUCION
		if ((strcmp(op1,"") && !strcmp(op2,"") && !strcmp(op3,"")) && strcmp(opcode,"NOP") && strcmp(opcode,"SYSCA") && strcmp(opcode,"JR") && strcmp(opcode,"MFLO") && strcmp(opcode,"MFHI")){	//vérifie type J: si op1 non vide et op2 et op3 sont vides. EXCLURE NOP ET SYSCALL
//-----------CAS J--------------------------------------------------------------------------------------------------

			while (i<2 && strcmp(opcode,codeJ[i])){								//cherche la traduction binaire de l'opcode
				i++;
				indice = i;
			}
				convertionBinaire(memmove(tmp,op1+1,5),op1T,26);
				sprintf(ligneTrad,"%6s%26s",codeEqJ[indice],op1T);			// enleve le \0 en fin de chaîne et ajouté les 02
				i=0;
		}
//----------CAS I------------------------------------------------------------------------------------------------
		else if((strchr(op3,'$') == NULL && strcmp(opcode,"SLL") && strcmp(opcode,"SRL") && strcmp(opcode,"ROTR") && strcmp(opcode,"NOP") && strcmp(opcode,"SYSCA") && strcmp(opcode,"JR") && strcmp(opcode,"DIV") && strcmp(opcode,"MULT") && strcmp(opcode,"MFLO") && strcmp(opcode,"MFHI")) || !strcmp(opcode,"SW") || !strcmp(opcode,"LW")){	//vérifie le type I: op3 est un offset. EXCLURE SA

			while (i<8 && strcmp(opcode,codeI[i])){									//cherche la traduction binaire de l'opcode
				i++;
				indice = i;
			}
//------------EXCEPTION---------------------------------------------------------------------------------------------

			if(!strcmp(opcode,"BLEZ") || !strcmp(opcode,"BGTZ")){		//cas de BLEZ et BGTZ
				strcpy(tmp,op2T);
				strcpy(op2T,op3T);
				strcpy(op3T,tmp);

				strcpy(tmp,op2T);
				strcpy(op2T,op1T);
				strcpy(op1T,tmp);

			}
			if (!strcmp(opcode,"LUI")){
				strcpy(tmp,op3T);
				strcpy(op3T,op2T);
				strcpy(op2T,tmp);

			}
			if(!strcmp(opcode,"LW") || !strcmp(opcode,"SW")){
				strcpy(tmp,op3T);
				strcpy(op3T,op2T);
				strcpy(op2T,tmp);
			}
				sprintf(ligneTrad,"%6s%5s%5s%16s",codeEqI[indice],op2T,op1T,op3T);	// enlevé le \0 en fin de chaîne et ajouté les 02
				i=0;

		}
//--------CAS R------------------------------------------------------------------------------------------------------
		else{																									//vérifie le type R. EXCLURE ROTR
			while (i<16 && strcmp(opcode,codeR[i])){
				i++;
				indice = i;
			}
//------------EXCEPTION---------------------------------------------------------------------------------------------
			if (!strcmp(opcode,"DIV") || !strcmp(opcode,"MULT")){
				strcpy(tmp,op1T);
				strcpy(op1T,op2T);
				strcpy(op2T,tmp);

				strcpy(tmp,op3T);
				strcpy(op3T,op1T);
				strcpy(op1T,tmp);
			}
			sprintf(ligneTrad,"000000%5s%5s%5s00000%6s",op2T,op3T,op1T,codeEqR[indice]);	// enlevé le \0 en fin de chaîne et ajouté les 02

			if(!strcmp(opcode,"ROTR") || !strcmp(opcode,"SLL") || !strcmp(opcode,"SRL")){
				int R = 1;
				if (!strcmp(opcode,"SLL")){
					R = 0;
				}
				sprintf(ligneTrad,"0000000000%d%5s%5s%5s%6s",R,op2T,op1T,op3T,codeEqR[indice]);

			}
			i=0;
		}
		indice = 0;
//---------------Ecriture dans le fichier---------------------------------------------------------------


		ligneHex1=conversionDecimal(ligneTrad,4);
		ligneHex2=conversionDecimal(ligneTrad+4,4);
		ligneHex3=conversionDecimal(ligneTrad+8,4);
		ligneHex4=conversionDecimal(ligneTrad+12,4);
		ligneHex5=conversionDecimal(ligneTrad+16,4);
		ligneHex6=conversionDecimal(ligneTrad+20,4);
		ligneHex7=conversionDecimal(ligneTrad+24,4);
		ligneHex8=conversionDecimal(ligneTrad+28,4);

		sprintf(ligneTrad,"%x%x%x%x%x%x%x%x",ligneHex1,ligneHex2,ligneHex3,ligneHex4,ligneHex5,ligneHex6,ligneHex7,ligneHex8);
		fprintf(sortie, "%s\n", ligneTrad);			// Ecriture dans un fichier


	}
	printf("Fichier entierement traduit sans problème\n");	//vérifie qu'on est arriver au bout
}

#ifdef TESTS
int main(int argc, char* argv[]){
		decodage(argv[1],argv[2]);
}
#endif
