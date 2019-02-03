#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NBFILS 10

int fonctionDeMerde(int n)
{
  int m = 1;
  if (n == 0)
  {
    printf("je suis le pere, mon ID est %d\n", getpid());
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
      printf("je suis un fils %d, mon ID est %d\n", (NBFILS - n + 1), getpid());
      exit (0);
    }
    else
    {
      sleep(1);
      m = fonctionDeMerde(n-1);
      while (m!=0);
      exit (0);
    }
  }
}

int main(int argc, char const *argv[])
{
  fonctionDeMerde(NBFILS);
  return 0;
}
