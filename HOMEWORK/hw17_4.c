// Сделано на семинаре
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int main(int argc, char const *argv[]) {
	int fd1[2], fd2[2];
	long long mx = strtoll(argv[1], NULL, 0);
	if (pipe(fd1) == -1)
		return 1;
	if (pipe(fd2) == -1)
		return 1;
	pid_t pid1 = fork();
	if (pid1 < 0) {
		exit(1);
	}
	if (!pid1) {
		int cnt = 1;
		while (cnt < mx) {
			if (cnt == 1) {
				printf("1 %d\n", cnt);
				cnt++;
				write(fd1[1], &cnt, sizeof(cnt));
			} else {
				if (read(fd2[0], &cnt, sizeof(cnt)) == sizeof(cnt)) {
					if (cnt < mx) {
						printf("1 %d\n", cnt);
						fflush(stdout);
					} else {
						close(fd1[0]);
						close(fd1[1]);
						close(fd2[0]);
						close(fd2[1]);
						while(wait(NULL) != -1)
						_exit(0);
					}
				} else {
					close(fd1[0]);
					close(fd1[1]);
					close(fd2[0]);
					close(fd2[1]);
					while(wait(NULL) != -1)
					_exit(0);
				}
				cnt++;
				write(fd1[1], &cnt, sizeof(cnt));
			}
		}

		// while(read(fd1[0], &val, sizeof(val)) == sizeof(val)) {
		// 	printf("2 %d\n", val);
		// }

		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);
		while(wait(NULL) != -1);
		_exit(0);
	}

	pid_t pid2 = fork();
	if (pid2 < 0) {
		exit(1);
	}

	if (!pid2) {
		int cnt = 1;
		while (cnt < mx) {
			if (read(fd1[0], &cnt, sizeof(cnt)) == sizeof(cnt)) {
				if (cnt < mx) {
					printf("2 %d\n", cnt);
					fflush(stdout);
				} else {
					close(fd1[0]);
					close(fd1[1]);
					close(fd2[0]);
					close(fd2[1]);
					while(wait(NULL) != -1)
					_exit(0);
				}
			} else {
				close(fd1[0]);
				close(fd1[1]);
				close(fd2[0]);
				close(fd2[1]);
				while(wait(NULL) != -1)
				_exit(0);
			}
			cnt++;
			write(fd2[1], &cnt, sizeof(cnt));
		}

		// while(read(fd2[0], &val, sizeof(val)) == sizeof(val)) {
		// 	printf("1 %d\n", val);
		// }
		close(fd1[0]);
		close(fd1[1]);
		close(fd2[0]);
		close(fd2[1]);
		_exit(0);
	}
	close(fd1[0]);
	close(fd2[0]);
	close(fd1[1]);
	close(fd2[1]);
	while(wait(NULL) != -1);
	printf("Done");
	fflush(stdout);
	exit(0);
	return 0;
}