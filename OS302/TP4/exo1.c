#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int static compteur = 0;

void fonction1 (int nbSignal) 
{
	printf ("nbSignal %d\n", nbSignal);
}

void fonction2 (int nbSignal) 
{
	printf ("nbSignal %d\n", nbSignal);
}


int main ()
{
	int pid = fork();
	
	if (pid < 0) 		perror ("erreur de fork"), exit (-1);		// cas d'erreur
	
	signal (SIGUSR1 , fonction1);
	signal (SIGUSR2 , fonction2);
	
	if (pid == 0) 				// on rentre dans le fils
	{
		for (int i = 2; i <= 100; i += 2)	
		{
			kill (SIGUSR2, getppid());
		}
		printf("\n");
	}

	else 					// on rentre dans le père		// naturellement, le père commence
	{
		for (int i = 1; i <= 100; i += 2)	
		{
			kill (SIGUSR1, pid);
		}
		printf("\n");
	}


	return 0;
}