#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// int static compteur = 0;

void nothing (int nbSignal)
{
//	printf ("signal envoyé\n");
}


int main ()
{
	int fils = fork();

	if (fils == -1) 								// cas d'erreur
	{
		printf("erreur de fork\n");
		exit (-1);
	}

	if (signal (SIGUSR1 , nothing) == SIG_ERR) 		printf("erreur signal\n");


	if (fils == 0) 									// on rentre dans le fils
	{
		printf("je suis le fils\n");
		int pere = getppid();
		for (int i = 1; i < 100; i += 2)
		{
			printf("%d\n", i);
			kill (pere, SIGUSR1);
			sleep (1);
		}
	}

	else 											// on rentre dans le pere		// naturellement, le pere commence
	{
//		sleep (5);									// une fois décommentée, cette ligne permet l'exécution du père PUIS du fils
		for (int i = 0; i <= 100; i += 2)
		{
			printf("%d\n", i);
			kill (fils, SIGUSR1);
			sleep (1);
		}
	}

	return 0;
}
