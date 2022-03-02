#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int main(int argc, char const *argv[]) {
	int fd[2]; // fd[1] - запись, fd[0] - чтение
	if (pipe(fd) == -1)
		return 1;
	pid_t pid1 = fork();
	if (pid1 < 0) {
		exit(1);
	}

	if (!pid1) {
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		execlp(argv[1], argv[1], NULL);
		// while(wait(NULL) != -1)
		_exit(0);
	}

	pid_t pid2 = fork();

	if (pid2 < 0) {
		exit(1);
	}

	if (!pid2) {
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		execlp(argv[2], argv[2], NULL);
		// while(wait(NULL) != -1)
		_exit(0);
	}

	close(fd[1]);

	pid_t pid3 = fork();

	if (pid3 < 0) {
		exit(1);
	}

	if (!pid3) {
		close(fd[1]);
		dup2(fd[0], 0);
		int f = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0600);
		dup2(f, STDOUT_FILENO);
		execlp(argv[3], argv[3], NULL);
		close(fd[0]);
		// while(wait(NULL) != -1)
		_exit(0);
	}

	close(fd[0]);
	wait(NULL);
	wait(NULL);
	wait(NULL);

	return 0;	
}