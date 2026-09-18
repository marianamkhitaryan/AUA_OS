#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

    // Assigment 3: Fork and Exec with Arguments

    pid_t ret = fork();

    if (ret < 0) {

        perror("fork failed");
        return 1;

    }

    if (ret == 0) {

        execl("/bin/echo", "echo", "Hello from the child process", NULL);

        perror("execl");
        return 1;

    }
    else {

        printf("Parent process done\n");

    }

    return 0;

}
