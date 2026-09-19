#include <stdio.h>
#include <stdlib.h>

void function1() {
    printf("Function 1 called\n");
}

void function2() {
    printf("Function 2 called\n");
}

int main() {

    //Test 1
    atexit(function1);
    atexit(function2);

    printf("Main function is running\n");

    exit(0);

    //Test 2
    // atexit(function1);
    // atexit(function2);

    // printf("Before exit\n");

    // exit(0);

    // printf("After exit\n");

    //Test 3
    // atexit(function1);
    // atexit(function2);

    // printf("Starting program\n");

    // if (1) {
       //  printf("Exiting now\n");
        // exit(0);
    // }

    // printf("End of program\n");

    // return 0;
}

