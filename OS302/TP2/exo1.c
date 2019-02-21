#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>


int main(void)
{
    int Nb_Sig;
    for(Nb_Sig = 1; Nb_Sig < NSIG ; Nb_Sig ++)
    {
        if (Nb_Sig != 10 && Nb_Sig != 12)   if (signal (Nb_Sig, SIG_IGN) == SIG_ERR)    printf("Impossible d'ignorer le signal %d : %s\n", Nb_Sig, strsignal(Nb_Sig));
    }

    signal (10, SIG_DFL);
    signal (12, SIG_DFL);

    while (1)	sleep(5);		/* Attendre les signaux */
    return 0;
}
