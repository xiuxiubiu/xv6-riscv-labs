
// sleep.c: sleep specific seconds

#include "../kernel/types.h"
#include "user.h"

int main(int argc, char **argv) {

	if (argc <= 1) {
		printf("please type number of sleep seconds\n");
		exit(1);
	}

	sleep(atoi(argv[1]));
	exit(0);
}
