#include "fraction.h"

int pgcd (int a, int b) {							// récupérée du TP1
	if (b == 0) return (a);
	else return (pgcd (b, a%b));
}

Fraction moins_denominateur (Fraction retour) {		// cette fonction sera appelé dans chaque fonction de calcul sur des fractions
	if (retour.den < 0) {
		retour.num = retour.num * (-1);
		retour.den = retour.den * (-1);
	}
	return (retour); 
}

void addFraction(Fraction f1, Fraction f2) {
	Fraction retour;
	retour.num = (f1.num*f2.den + f2.num*f1.den);
	retour.den = (f1.den*f2.den);
	int diviseur = 0;
	while (diviseur != 1) {
		diviseur = pgcd(retour.num, retour.den);
		retour.num = retour.num / diviseur;
		retour.den = retour.den / diviseur;
	}	
	moins_denominateur (retour);
	printf ("%d/%d + %d/%d = %d/%d\n", f1.num, f1.den, f2.num, f2.den, retour.num, retour.den);
}

void subFraction(Fraction f1, Fraction f2) {
	Fraction retour;
	retour.num = (f1.num*f2.den - f2.num*f1.den);
	retour.den = (f1.den*f2.den);
	int diviseur = 0;
	while (diviseur != 1) {
		diviseur = pgcd(retour.num, retour.den);
		retour.num = retour.num / diviseur;
		retour.den = retour.den / diviseur;
	}
	moins_denominateur (retour);
	printf ("%d/%d - %d/%d = %d/%d\n", f1.num, f1.den, f2.num, f2.den, retour.num, retour.den);
}

void mulFraction(Fraction f1, Fraction f2) {
	Fraction retour;
	retour.num = (f1.num*f2.num);
	retour.den = (f1.den*f2.den);
	int diviseur = 0;
	while (diviseur != 1) {
		diviseur = pgcd(retour.num, retour.den);
		retour.num = retour.num / diviseur;
		retour.den = retour.den / diviseur;
	}
	moins_denominateur (retour);
	printf ("%d/%d * %d/%d = %d/%d\n", f1.num, f1.den, f2.num, f2.den, retour.num, retour.den);
}

void divFraction(Fraction f1, Fraction f2) {
	Fraction inv2 = {f2.den, f2.num};
	
	Fraction retour;
	retour.num = (f1.num*inv2.num);
	retour.den = (f1.den*inv2.den);
	int diviseur = 0;
	while (diviseur != 1) {
		diviseur = pgcd(retour.num, retour.den);
		retour.num = retour.num / diviseur;
		retour.den = retour.den / diviseur;
	}
	moins_denominateur (retour);
	printf ("%d/%d / %d/%d = %d/%d\n", f1.num, f1.den, f2.num, f2.den, retour.num, retour.den);
}


int main (){
	Fraction fa, fb;
	char op;
	printf("Entrer deux fractions :\t");
	scanf("%d/%d %d/%d", &fa.num, &fa.den, &fb.num, &fb.den);
	printf("Entrer une opération (+, -, /, *) : \t"); 					// demander à Lorine
	scanf("%c", &op);
	if (op == '+')	addFraction (fa, fb);
	else if (op == '-')	subFraction (fa, fb);
	else if (op == '*')	mulFraction (fa, fb);
	else if (op == '/')	divFraction (fa, fb);
	else printf("Mauvais caractere, relancez le programme\n");
	return (0);
	
}












