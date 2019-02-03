#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
  signal (SIGINT, SIG_IGN);
  while (1) sleep (1);
  return 0;
}
