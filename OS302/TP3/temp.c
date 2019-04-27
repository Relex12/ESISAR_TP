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
		kill (SIGUSR1, getppid());
/*		for (int i = 2; i <= 100; i += 2)
		{
			pause();
			printf("%d\t", i);
			kill (SIGUSR2, getppid());
		}
*/		printf("fils\n");
	}

	else 					// on rentre dans le pere		// naturellement, le pere commence
	{
		kill (SIGUSR1, pid);


/*		printf("%d\t", 1);
		kill (SIGUSR1, pid);
		for (int i = 2; i <= 100; i += 2)
		{
			pause();
			printf("%d\t", i);
			kill (SIGUSR1, pid);
		}
*/		printf("père\n");
	}


	return 0;
}



















#define NBMININHOU 6		// nombre de secondes dans une minute
#define NBSECINMIN 4		// nomnre de minutes dans une heure

void fctrien(int a) {}



int main(){
	int h, m,s;
	int nbSec;
	h = getpid();
	signal(SIGUSR1,fctrien);
	if((m = fork()) == -1) return -1;


	if(m == 0)														// dans le processus M
	{
		for(nbSec = 0; nbSec <= NBSECINMIN; nbSec++)
		{
			printf("minute = %d seconde = 0\n",nbSec);
			if(nbSec == NBSECINMIN)
			{
				kill (h, SIGUSR1);
				nbSec = 0;
			}
			pause();
		}
	}


	else
	{
		if((s = fork()) == -1) return -1;
			if(s == 0)												// dans le processus S
			{
				signal (SIGALRM, fctrien);
				for(nbSec = 0; nbSec <= NBMININHOU; nbSec++)
				{
					alarm (1);
					printf("seconde = %d\n",nbSec);
					if(nbSec == NBMININHOU )
					{
						kill (m, SIGUSR1);
						nbSec = 0;
					}
					pause();
				}
			}
			else													// dans le processus H
			{
				for(nbSec = 0; nbSec < 60; nbSec++)
				{
					printf("heure = %d minute = 0 seconde = 0\n",nbSec);
					pause();
				}

			}


	}
}
