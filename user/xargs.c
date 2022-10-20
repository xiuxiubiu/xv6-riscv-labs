
// xargs.c: it's arguments describe a command to run, it reads lines from the standard input,
// and it runs the command for each lines, appending the line to the command's arguments.

#include "../kernel/types.h"
#include "../kernel/param.h"
#include "user.h"

#define ARGLEN 512

int forkexec(char *, char **);

int main(int argc, char **argv) {

	if (argc < 2) {
		printf("xargs: [command] [args] ...\n");
		exit(1);
	}

	if (argc - 2 > MAXARG) {
		printf("xargs: command has too many argumnets.\n");
		exit(1);
	}


	char c;
	char *args[MAXARG];		
	char buf[512];
	char *p;
	int i;

	for (i = 1; i < argc; i++)
		args[i-1] = argv[i];

	for (p = buf; read(0, &c, 1); p++) {
		if (c == '\n' || c == '\0') {
			*p = '\0';
			args[i-1] = buf; 
			args[i] = 0;
	
			if (forkexec(argv[1], args) != 0) {
				printf("xargs: forkexec err\n");
				exit(1);
			}
			p = buf;
		} else  
			*p = c;
	}

	exit(0);
}

int forkexec(char *file, char **args) {

	if (fork() == 0) {
		exec(file, args);
		return 1;
	} else 
		wait((int *)0);
	
	return 0;
}
