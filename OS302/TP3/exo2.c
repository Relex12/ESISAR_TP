#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

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
