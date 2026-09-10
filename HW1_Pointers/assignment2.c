#include <stdio.h>

int main() {
    // Assignment 2: Pointer Arithmetic

    int arr[5] = {5, 7, 45, 32, 9};
    int *p = arr;

    for (int i = 0; i < 5; i++) {
        printf("The value of arr[%d] is: %d\n", i, *(p + i));

        *(p + i) *= 4;
        printf("The new value of arr[%d] using pointer arithmetic is: %d\n", i, *(p + i));
        printf("The new value of arr[%d] using array name is: %d\n \n", i, arr[i]);

    }
}
