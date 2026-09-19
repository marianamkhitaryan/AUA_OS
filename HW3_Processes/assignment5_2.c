#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        printf("Child: PID = %d\n", getpid());
        exit(0);
    } else {
        printf("Parent: PID = %d\n", getpid());

        wait(NULL);

        printf("Parent: child has finished\n");
    }

    return 0;
}
