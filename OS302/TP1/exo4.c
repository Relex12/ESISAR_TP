#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NBFILS 10

int creaRecur(int n)
{
    if (n <= 0)
    {
        printf("Pere : mon ID est %d\n", getpid());
        return 0;
    }

    else
    {
        int pid = fork();
        if (pid == -1)
        {
            perror ("Creaction de processus");
            exit (2);
        }
        else if (pid == 0)
        {
            printf("Fils %d : mon PID est : %d et celui de mon père : %d\n", n, getpid(), getppid());
            sleep(2*n);
            printf("\nFils : fin d'attente (PID %d)\n",getpid());
            exit (n);
        }
        else
        {
            sleep(1);
            creaRecur(n-1);
            int Etat;
            int ret_fils = wait(&Etat);
            printf("Pere : un fils est mort : PID %d, etat : %d\n", ret_fils, Etat);
            if (ret_fils == -1) printf("\nPere : tous les fils sont morts, fin du père de PID %d\n", getpid());
        }
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    creaRecur(atoi (argv[1]));
    return 0;
}
