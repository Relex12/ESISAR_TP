#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void maFonction (int sig)
{
  static int nb = 0;
  if (sig == SIGINT)  printf("Bien essaye, tentative %d\n", ++nb);
  if (nb >= 5)        signal (SIGINT, SIG_DFL);
}

int main(int argc, char const *argv[]) {
  signal (SIGINT, maFonction);
  while (1) sleep (1);
  return 0;
}
