#include <stdio.h>
#include <math.h>

#define MAX 20

int myStrlen (char* mot)
{
	int nb = 0;
	while (mot[nb] != '\0')		nb++;
	return nb;
}

char* myStrcpy (char* dest, char* src)
{
	int i = 0;
	while (src[i] != '\0')	
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return dest;
}

void afficheHexa (char* mot)
{
	int i = 0;
	printf ("valeur en hexa de %s :\t0x", mot);
	while (mot[i] != '\0')		
	{
		printf ("%x", mot[i]);
		i++;
	}
	printf ("\n");
}

void afficheDeci (char* mot)
{
	int i = 0;
	int valeur = 0;
	printf ("valeur en décimal de %s :\t", mot);
	while (mot[i] != '\0')		
	{
		valeur = (int) mot[i];
		printf ("%d", valeur);
		i++;
	}
	printf ("\n");
}

int myIsLower (char c)				//testee et approuvee
{
	return (c >= 0x61 && c <= 0x7a);
}

int myIsUpper (char c)				//testee et approuvee
{
	return (c >= 0x41 && c <= 0x5a);
}

char* Uppercase (char mot[])
{
	int i = 0;
	while (mot[i] != '\0')		
	{
		if (myIsLower(mot[i]))	mot[i] = mot[i] - 0x20;
		i++;
	}
	return mot;
}

char* Lowercase (char mot[])
{
	int i = 0;
	while (mot[i] != '\0')		
	{
		if (myIsUpper(mot[i]))	mot[i] = mot[i] + 0x20;
		i++;
	}
	return mot;
}

char* switchCase (char mot[])
{
	int i = 0;
	while (mot[i] != '\0')		
	{
		if (myIsUpper(mot[i]))		mot[i] = mot[i] + 0x20;
		else if (myIsLower(mot[i]))	mot[i] = mot[i] - 0x20;
		i++;
	}
	return mot;
}

char* reverse (char* mot, char* res)
{	
	int lenght = myStrlen(mot);
//	for (int i = 0; i < lenght; i++)	temp[i] = mot[i];
	for (int i = 0; i < lenght; i++)	res[i] = mot[lenght-i-1];
	return res;
}

int findLeft (char* mot, char lettre)
{	
	int i = 0;
	while (mot[i] != '\0' && mot[i] != lettre)		
	{
		i++;
	}
	return (i+1);
}

int findRight (char* mot, char lettre)
{	
	int lenght = myStrlen(mot);
	int i = 0;
	while (mot[i] != '\0' && mot[lenght-i-1] != lettre)		
	{
		i++;
	}
	return (i+1);
}

int myStrcmpr (char* mot1, char* mot2)
{
	int lenght = myStrlen(mot1);
	for (int i = 0; i <= lenght; i++) 	if (mot1[i] != mot2[i])		return 0;
	return 1;
}

int palindrome (char* mot) 
{
	char temp[] = "example";
	return (myStrcmpr (mot, reverse(mot, temp)));
}


int main ()
{
	char mot[] = "arbre";
	char res[MAX];
	printf ("la longueur de %s est : %d\n", mot, myStrlen(mot));
	printf ("test de myStrcpy : %s\n", myStrcpy (res, mot));
	afficheHexa(mot);
	afficheDeci(mot);

	printf ("mise en maj de %s :\t", mot);	printf ("%s\n", Uppercase(mot));
	printf ("mise en min de %s :\t", mot);	printf ("%s\n", Lowercase(mot));
	printf ("switch case de %s :\t", mot);	printf ("%s\n", switchCase(mot));
	printf ("switch case de %s :\t", mot);	printf ("%s\n", switchCase(mot));
	
	printf ("inversion de %s :\t", mot);
	printf ("%s\n", reverse(mot, res));
	
	char lettre = 'a';
	printf ("dans %s, %c est à la %d eme position (gauche)\n", mot, lettre, findLeft (mot, lettre));
	printf ("dans %s, %c est à la %d eme position (droite)\n", mot, lettre, findRight (mot, lettre));
	
	printf ("palindrome (%s) = %d\n", mot, palindrome (mot));
	return 0;
}
