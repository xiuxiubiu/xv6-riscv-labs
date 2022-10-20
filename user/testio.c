#include "../kernel/types.h"
#include "user.h"

int main() {
	int fd;

	if (fork() == 0) {
		write(1, "hello ", 6);
		exit(0);
	} else {
		wait((int *)0);
		write(1, "world\n", 6);
	}

	fd = dup(1);
	printf("new fd: %d\n", fd);
	write(1, "hello ", 6);
	write(fd, "world\n", 6);

	exit(0);
}
