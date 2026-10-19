
#include <stdio.h>

struct Struct1 {
    char a;
    int b;
    double c;
};

struct Struct2 {
    double c;
    int b;
    char a;
};

int main() {
    struct Struct1 s1;
    struct Struct2 s2;

    printf("Struct1 size: %zu bytes\n", sizeof(s1));
    printf("Struct1 addresses:\n");
    printf("a: %p\n", (void *)&s1.a);
    printf("b: %p\n", (void *)&s1.b);
    printf("c: %p\n", (void *)&s1.c);

    printf("\nStruct2 size: %zu bytes\n", sizeof(s2));
    printf("Struct2 addresses:\n");
    printf("c: %p\n", (void *)&s2.c);
    printf("b: %p\n", (void *)&s2.b);
    printf("a: %p\n", (void *)&s2.a);

    return 0;
}
