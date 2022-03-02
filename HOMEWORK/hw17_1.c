// Сделано на семинаре
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
	int fd[2];
	pipe(fd);

	pid_t pid1 = fork();
	if (pid1 < 0) {
		exit(1);
	}

	if (!pid1) {
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);

		execlp(argv[1], argv[1], NULL);
		_exit(1);
	}
	

	pid_t pid2 = fork();
	if (pid2 < 0) {
		exit(1);
	}

	if (!pid2) {
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		execlp(argv[2], argv[2], NULL);
		_exit(1);
	}
	
	close(fd[0]);
	close(fd[1]);

	wait(NULL);
	wait(NULL);
	return 0;	
}