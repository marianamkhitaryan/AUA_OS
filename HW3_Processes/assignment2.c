#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t child1, child2;
    int status;

    child1 = fork();

    if (child1 < 0) {
        perror("fork failed");
        return 1;
    }

    if (child1 == 0) {
        printf("Child 1: PID = %d\n", getpid());
        sleep(2);
        exit(10);
    }

    child2 = fork();

    if (child2 < 0) {
        perror("fork failed");
        return 1;
    }

    if (child2 == 0) {
        printf("Child 2: PID = %d\n", getpid());
        sleep(1);
        exit(20);
    }

    waitpid(child2, &status, 0);

    if (WIFEXITED(status)) {
        printf("Child 2 exit status: %d\n", WEXITSTATUS(status));
    }

    wait(&status);

    if (WIFEXITED(status)) {
        printf("Child 1 exit status: %d\n", WEXITSTATUS(status));
    }

    return 0;
}
