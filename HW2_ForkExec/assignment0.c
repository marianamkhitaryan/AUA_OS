#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    // Assignment 0: Multiple Fork calls
    
    pid_t ret;

    ret = fork();
    if (ret < 0){
	perror("fork failed");
	return 1;
    }
  
    ret = fork();
    if (ret < 0){
        perror("fork failed");
        return 1;
    }

    ret = fork();
    if (ret < 0){
        perror("fork failed");
        return 1;
    }

    printf("process PID = %d, parent PID = %d\n", getpid(), getppid());

    return 0;
}



