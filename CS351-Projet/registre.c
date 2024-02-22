#include "registre.h"

int lectureReg (int registreVal)
{
	if (registreVal > 34) return -1;	// plus grand que le nombre de registres
	else if(registreVal < 0) return -1;	// n'a pas de sens
	else if(registreVal = 34) return LO;
	else if(registreVal = 33) return HI;
	else if(registreVal = 32) return PC;
	else return registre[registreVal];
}

void ecritureReg (int registreVal, int data)
{
	if (registreVal > 34) printf("ACTION IMPOSSIBLE (>34)\n");	// plus grand que le nombre de registres
	else if(registreVal < 0) printf("ACTION IMPOSSIBLE (<0)\n");	// n'a pas de sens
	else if(registreVal = 34) LO = data;
	else if(registreVal = 33) HI = data;
	else if(registreVal = 32) PC = data;
	else registre[registreVal] = data ;
}

int conversionNomVal (char * registreNom) 	// renvoie la valeur du registre
{
	int i = 0;
	while (i < 35 && strcmp(conversion[i], registreNom)) i++;
	if (i < 35)		return i;
	printf("NOM DE REGISTRE INTROUVABLE\n");
	return (-1);
}


#ifdef TESTS
int main(int argc, char const *argv[])
{
	for (int i = 0; i <= 36; i++)
	{
		ecritureReg (i-1, i);
		printf("la valeur du registre n°%d est : %d\n", i-1, lectureReg (i-1));
	}

	for (int i = 0; i <= 34; i++)
	{
		printf("le numéro du registre %s est : %d\n", conversion[i], conversionNomVal (conversion[i]));
	}

	printf("le numéro du registre %s est : %d\n", "prout", conversionNomVal ("prout"));


	return 0;
}
#endif
