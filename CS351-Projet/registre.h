#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* conversion[35] = {"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gr", "sp", "fp", "ra", "pc", "hi", "lo"};

int registre[32];
int PC;			// la valeur correspondante utilisée sera 32
int HI;			// la valeur correspondante utilisée sera 33
int LO;			// la valeur correspondante utilisée sera 34

int lectureReg (int registreVal);
void ecritureReg (int registreVal, int data);
int conversionNomVal (char * registreNom); 	// renvoie la valeur du registre
