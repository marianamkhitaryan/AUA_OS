#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

    // Assignment 1: Simple Fork and Exec

    pid_t ret = fork();

    if (ret < 0) {
	perror("fork failed");
	return 1;
    }

    if (ret == 0) {

        execl("/bin/ls", "ls", NULL);

	perror("execl");
	return 1;

    }
    else {

	printf("Parent process done\n");

    }

    return 0;

}
