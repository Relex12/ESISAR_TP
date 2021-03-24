#include <signal.h>
#include <unistd.h>
int main (void){
  /* ...
    Mettre ici le traitement pour tous les signaux
    sauf SIGUSR1 et SIGUSR2. */
  ... */
  /* Mettre ici le traitement pour SIGUSR1 et SIGUSR2
  ... */
  while (1){
    sleep(5);
  } /* Attendre les signaux */
  return 0;
}
/*************** La fonction fonc **************/
void fonc (int NumSignal){
//...
}
/*************** La fonction fonc1 **************/
void fonc1 (int NumSignal){
//...
}
/*************** La fonction fonc2 **************/
void fonc2 (int NumSignal){
//...
}
