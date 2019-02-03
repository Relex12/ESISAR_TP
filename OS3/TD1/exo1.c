#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
  int pid1 = fork();
  int pid2;
  if (pid1 == -1)
  {
    perror ("Creaction de processus");
    exit (2);
  }
  else if (pid1 == 0)
  {
    printf("je suis un fils 1, mon ID est %d\n", getpid());
    sleep (2);
    exit (0);
  }
  else
  {
    pid2 = fork();
    if (pid2 == -1)
    {
      perror ("Creaction de processus");
      exit (2);
    }
    else if (pid2 == 0)
    {
      printf("je suis un fils 2, mon ID est %d\n", getpid());
      sleep (2);
      exit (0);
    }
    else
    {
      printf("je suis le père, mon ID est %d\n", getpid());
      waitpid(pid1, NULL, 0);
      printf("je suis navre de vous apprendre le deces de mon fils au PID %d\n", pid1);
      exit (0);
    }
  }
  return 0;
}
