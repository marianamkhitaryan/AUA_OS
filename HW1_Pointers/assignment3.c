#include <stdio.h>

int swap(int *a, int *b) {

    int temp = *a;
    *a = *b;
    *b = temp;

    return 0;
}

int main() {
    // Assignment 3: Pointers and Functions

    printf("\nAssignment 3: Pointers and Functions\n");

    int a = 56;
    int b = 4;

    printf("The value of a before swap is: %d\n", a);
    printf("The value of b before swap is: %d\n", b);

    swap(&a, &b);

    printf("The value of a after swap is: %d\n", a);
    printf("The value of b after swap is: %d\n", b);
}