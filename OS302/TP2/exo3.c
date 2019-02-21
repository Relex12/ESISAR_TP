#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>



void fonc (int NumSignal)
{
	printf("\nsignal %d recu\n", NumSignal);
}

void fonc1 (int NumSignal)
{
	printf("\nsignal %d recu\n", NumSignal);
	system("who");
}

void fonc2 (int NumSignal)
{
	printf("\nsignal %d recu\n", NumSignal);
	system("df .");
}


int main (void)
{
	printf("Fils : PID %d\n", getpid());

	int Nb_Sig;
    for(Nb_Sig = 1; Nb_Sig < NSIG ; Nb_Sig ++) 		signal (Nb_Sig, fonc);

    signal (SIGUSR1, fonc1);
    signal (SIGUSR2, fonc2);

	  while (1)		sleep(5);/* Attendre les signaux */
	  return 0;
}
