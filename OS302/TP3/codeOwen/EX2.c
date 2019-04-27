#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>



void * fctrien(int a)
{

}



int main(){
	int pid_pere;
	int h, m,s;
	int a;
	h = getpid();
	signal(SIGUSR1,fctrien);
	if((m = fork()) == -1) return -1;
	if(m == 0){
		for(a = 0; a<6; a++){
			printf("minute = %d seconde = 0\n",a);
			if(a == 5){
				kill(h,SIGUSR1);
				a = 0;
			}
			pause();
		}
	}
	else{
		if((s = fork()) == -1) return -1;
			if(s == 0){
				signal(SIGALRM,fctrien);
				for(a = 0; a<5; a++){
					alarm(1);
					printf("seconde = %d\n",a);
					if(a == 4){
						kill(m,SIGUSR1);
						a = 0;
					}
					pause();
				}
			}
			else{
				for(a= 0; a<60; a++){
					printf("heure = %d minute = 0 seconde = 0\n",a);
					pause();
				}
		
			}

		
	}
}
