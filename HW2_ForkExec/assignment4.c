#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

    // Assignment 4: Fork and Exec with Command-Line Arguments

    pid_t ret = fork();

    if (ret < 0) {

        perror("fork failed");
        return 1;

    }

    if (ret == 0) {

        execl("/usr/bin/grep", "grep", "main", "test.txt", NULL);

        perror("execl");
        return 1;

    }
    else {

        printf("Parent process completed\n");

    }

    return 0;

}
