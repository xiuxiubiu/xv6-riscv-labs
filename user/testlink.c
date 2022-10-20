#include "../kernel/types.h"
#include "user.h"
#include "../kernel/stat.h"
#include "../kernel/fs.h"
#include "../kernel/fcntl.h"

int main() {
	char *ori = "ls";
	char *new = "lslink";

	if (link(ori, new) < 0) {
		printf("link err\n");
		exit(1);
	}

	printf("link success!\n");

	int ori_fd, new_fd;
	struct stat ori_st, new_st;

	if ((ori_fd = open(ori, O_RDWR)) < 0) {
		printf("open file: %s err\n", ori);
		exit(1);
	}

	if ((new_fd = open(new, O_RDWR)) < 0) {
		printf("open file: %s err\n", new);
		exit(1);
	}

	printf("ori fd: %d, new fd: %d\n", ori_fd, new_fd);

	// unlink(new);

	if (fstat(ori_fd, &ori_st) < 0) {
		printf("fstat fd: %d err\n", ori_fd);
		exit(1);
	}
	if (fstat(new_fd, &new_st) < 0) {
		printf("fstat fd: %d err\n", new_fd);
		exit(1);
	}
	
	printf(" dev: ori - %d, new - %d\n ino: ori - %d, new - %d\n type: ori - %d, new - %d\n\
 link: ori - %d, new - %d\n size: ori - %d, new - %d\n ",
		ori_st.dev, new_st.dev, ori_st.ino, new_st.ino, ori_st.type, new_st.type, 
		ori_st.nlink, new_st.nlink, ori_st.size, new_st.size
	);

	exit(0);
}
