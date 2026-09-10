#include <stdio.h>

int main() {

    // Assignment 5: Strings and Character Pointers
    char str[] = "Hello";
    char *p = str;

    int num = 0;

    for (int i = 0; i < sizeof(str) - 1; i++){

        num += 1;
        printf("The characters str[%d] is: %c\n", i, *(p + i));

    }

    printf("The number of characters in the string is: %d\n", num);

    return 0;
}