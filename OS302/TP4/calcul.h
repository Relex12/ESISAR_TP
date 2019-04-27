#ifndef __CALCUL_H
#define __CALCUL_H

#define MSGKEY 50				/* cle d'entree dans la table d'IPC (cf. ipcs) */

struct msg_struct               /* structure d'un message */
// Ajout des champs operande 1 et 2, operation et pid 
{
	long type;
	int operande1;
	int operande2;
	char operation;
	int pid;
};
#endif
