#include <stdio.h>

int main() {
    // Assignment 1: Basics of Pointers

    int a = 48;
    int *p = &a;

    printf("The value of a using integer is: %d\n", a);
    printf("The value of a using pointer is: %d\n", *p);

    *p += 50;
    printf("The new value of a is: %d\n", *p);

}