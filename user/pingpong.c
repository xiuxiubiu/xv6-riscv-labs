
// pingpong.c: call to 'ping-pong' a byte between two processes over a pair of pipes

#include "../kernel/types.h"
#include "user.h"

int
main() {

	int fds[2];
	if (pipe(fds) < 0) {
		printf("pipe create error!");
		exit(1);
	}


	write(fds[1], "ping", 4);

	int pid = fork();
	if (pid == 0) {

		char *ping = malloc(4);
		read(fds[0], ping, 4);
		printf("%d: received %s\n", getpid(), ping);

		write(fds[1], "pong", 4);

	} else {
		wait((int *)(0));

		char *pong = malloc(4);
		read(fds[0], pong, 4);
		printf("%d: received %s\n", getpid(), pong);
	}

	exit(0);
}
