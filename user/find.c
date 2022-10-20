
// find.c: find all the files in a directory tree with a specific name

#include "../kernel/types.h"
#include "user.h"
#include "../kernel/fcntl.h"
#include "../kernel/stat.h"
#include "../kernel/fs.h"

int find(char *, char *);

char *fmtname(char*);

int main(int argc, char **argv) {

	if (argc < 3) {
		printf("usage: find [directory] [name]\n");
		exit(0);
	}
	
	find(argv[1], argv[2]);

	exit(0); 
}

char *fmtname(char *path) {
	static char buf[DIRSIZ + 1];
	char *p;

	for (p = path + strlen(path); p >= path && *p != '/'; p--)
		;
	p++;

	strcpy(buf, p);
	
	return buf;
}

int find(char *path, char *name) {
		
	int fd;
	struct stat st;
	struct dirent de;
	char buf[512];
	char *p;
	
	if ((fd = open(path, O_RDONLY)) < 0) {
		fprintf(2, "find: cannot open %s\n", path);
		return -1;
	}
	
	if (fstat(fd, &st) < 0) {
		fprintf(2, "find: cannot stat %d\n", path);
		close(fd);
		return -1;
	}

	switch (st.type) {
		case T_FILE:
			if (strcmp(fmtname(path), name) == 0) {
				printf("%s\n", path);
			}
			break;

		case T_DIR:
			if (strlen(path) + 1 + DIRSIZ > sizeof(buf)) {
				printf("find: path too long!");
				break;
			}
			
			while (read(fd, &de, sizeof(de)) == sizeof(de)) {
				if (de.inum == 0) 
					continue;

				if (strcmp(".", de.name) == 0 || strcmp("..", de.name) == 0)
					continue;

				strcpy(buf, path);
				p = buf + strlen(buf);
				*p++ = '/';

				memmove(p, de.name, DIRSIZ);

				find(buf, name);
			}		

			break;
		default:
			break;
	}		

	close(fd);
	return 0;
}
