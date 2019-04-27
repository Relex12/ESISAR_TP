#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "calcul.h"


int main(int argc, char const *argv   [])
{
	int msg_id;
	struct msg_struct msg;
	if  (argc !=   4)
	{
		printf("Usage: %s operande1 {+|-|*|/} operande2\n", argv[0]);
		exit(-1);
	}

	/* il faut eviter la division par zero */
	/* A COMPLETER */
	if (msg.operande2 == 0 && msg.operation == '/')
	{
		printf("division de %d par 0\n", msg.operande1);
		exit(-1);
	}

	/* ATTENTION : la file de messages doit avoir ete creee par le serveur.
	Il faudrait  tester la valeur de retour (msg_id) pour
	verifier que cette creation a bien eu lieu.*/

	msg_id = msgget(MSGKEY, 0);				// MSGKEY défini comme la clé dans calcul.h, et 0 parce que je sais pas

	printf("CLIENT %d: preparation du message contenant l'operation suivante: %d %c %d\n",   getpid(),   atoi  (argv[1]), argv[2][0], atoi(argv[3]));

	/* On prepare un message de type 1 à envoyer au serveur avec les informations necessaires */
	/* A COMPLETER */
	msg.type = 1;
	msg.operande1 = (int) *argv[1];
	msg.operande2 = (int) *argv[3];
	msg.operation = (char) *argv[2];

	/* envoi du message */
	msgsnd(msg_id, &msg, sizeof(struct msg_struct) - sizeof(long), 0);

	/* reception de la reponse */
	msgrcv(msg_id, &res, sizeof(int), sizeof(int), 0);

	printf("CLIENT: resultat recu depuis le serveur %d : %d\n", msg_id,  msg);
	return 0;
}
