#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include "calcul.h"


void raz_msg(int);			/* routine de traitement des signaux */

int msg_id; 				/* identificateur de la file de messages */



int main(int argc, char const *argv   [])
{
	struct msg_struct msg;
	int i_sig; int result;

	/* liberer la zone de messages sur reception de n'importe quel signal */
	for (i_sig = 0; i_sig < NSIG; i_sig++)
	{
		signal(i_sig, raz_msg);
	}

	msg_id = msgget(MSGKEY, 0);

	printf("SERVEUR: pret!\n");
	while(1)
	{
		/* reception */
		msgrcv
		printf("SERVEUR: reception d'une requete de la part de: %d\n", msg_id);

		/* preparation de la reponse */
		/* A COMPLETER */
		resultat =

		/* envoi de la reponse */
		msgsnd(/* A COMPLETER */);
	}
	return 0;
}



void raz_msg(int signal)
{
	printf("Suppression de la file de message!\n");
	msgctl(/* A COMPLETER */);
	exit(0);
}
