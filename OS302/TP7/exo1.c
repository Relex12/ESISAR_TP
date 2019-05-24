#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>


int main(int argc, char const *argv[]) {
	int p[2];
	int pid_fils;
	if (pipe(p) == -1) {
		perror ("erreur creation pipe");
		exit (EXIT_FAILURE);
	}
	pid_fils = fork();
	if (pid_fils == 0) {
		waitpid(getppid(), NULL, 0);
		dup2(p[0], STDIN_FILENO);
		system(argv[2]);
		exit(0);
	}
	else {
		dup2(p[1], STDIN_FILENO);
		system(argv[1]);
		exit(0);
	}
	return 0;
}
