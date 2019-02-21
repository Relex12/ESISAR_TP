#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

void attente(int sig)
{
    sleep (2);
    signal(SIGINT, SIG_DFL);
    printf("Fils : deces iminent, PID = %d\n", getpid());
    kill (getpid(), SIGINT);
}

int main(int argc, char const *argv[]) {

// les parties en commentaires correspondes à une tentative d'implémentation de timer pour afficher le temps d'exécution
// ces timers affichent des temps d'exécution de l'ordre de 0.01 secondes, donc c'est pas comme ça que cela doit être implémenté

	int pid = fork();

    if (pid == -1)      perror("creation processus");
    else if (pid == 0)
    {
/*		float temps;
		clock_t t1, t2;
		t1 = clock();
*/		signal(SIGINT, attente);
/*		t2 = clock();
		temps = (float)(t2-t1)/CLOCKS_PER_SEC;
		printf("temps attente fils = %f\n", temps);
*/        while (1)   sleep(1);
    }

    else
    {
		printf("debut du programme\n");
/*		float temps;
		clock_t t1, t2;
		t1 = clock();
*/    	sleep (5);
/*		t2 = clock();
		temps = (float)(t2-t1)/CLOCKS_PER_SEC;
	    printf("temps attente pere = %f\n", temps);
*/		kill(pid, SIGINT);
        int Etat;
        wait(&Etat);
        printf("Pere : fils mort, PID %d, etat %d\n", pid, Etat);
    }
    return 0;
}
