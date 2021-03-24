#include <stdio.h>
#include <signal.h>
#include <unistd.h>
 
int main(void){
  int Nb_Sig;
  for(Nb_Sig = 1; Nb_Sig < NSIG ; Nb_Sig ++){
    ...
    ...
  }
  while(1){
    sleep(5);
  } /* Attendre des signaux */
  return 0;
}
