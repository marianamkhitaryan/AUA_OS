#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

    // Assignment 2: Multiple Forks and Execs

    pid_t ret1;
    pid_t ret2;

    ret1 = fork();

    if (ret1 < 0) {

	perror("fork failed");
	return 1;

    }

    if (ret1 == 0) {

	execl("/bin/ls", "ls", NULL);

	perror("execl");
	return 1;

    }

    ret2 = fork();

    if (ret2 < 0) {

        perror("fork failed");
        return 1;

    }

    if (ret2 == 0) {

        execl("/bin/date", "date", NULL);

        perror("execl");
        return 1;

    }

    printf("Parent process done\n");

    return 0;

}

