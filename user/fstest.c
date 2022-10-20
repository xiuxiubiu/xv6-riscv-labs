#include "../kernel/types.h"
#include "user.h"

int main() {
	int fds[2];

	if (fork() == 0) {
		if (pipe(fds) != 0)
			exit(1);

		printf("one: %d, two: %d\n", fds[0], fds[1]);
	}
	wait((int *)0);
	
	exit(0);
}
