#include <stdio.h>

int main() {
    // Assignment 4: Pointers to Pointers

    int a = 73;
    int *p = &a;
    int **pp = &p;

    printf("The value of a using the pointer is: %d\n", *p);
    printf("The value of a using the double-pointer is: %d\n", **pp);

    return 0;
}
