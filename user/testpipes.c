#include "../kernel/types.h"
#include "user.h"

int main() {

	int fds[2];

	pipe(fds);
	if (fork() == 0) {
		close(0);
		dup(fds[0]);	
		exec("/bin/wc", 0);
		

	} else {
		
		write(fds[1], "\n", 4);
		wait((int *)0);
	}

	exit(0);
}
