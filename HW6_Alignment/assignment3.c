
#include <stdio.h>

struct NormalStruct {
    char a;
    int b;
    double c;
};

#pragma pack(1)
struct PackedStruct {
    char a;
    int b;
    double c;
};
#pragma pack()

int main() {
    struct NormalStruct normal;
    struct PackedStruct packed;

    printf("Normal struct size: %zu bytes\n", sizeof(normal));
    printf("Normal addresses:\n");
    printf("a: %p\n", (void *)&normal.a);
    printf("b: %p\n", (void *)&normal.b);
    printf("c: %p\n", (void *)&normal.c);

    printf("\nPacked struct size: %zu bytes\n", sizeof(packed));
    printf("Packed addresses:\n");
    printf("a: %p\n", (void *)&packed.a);
    printf("b: %p\n", (void *)&packed.b);
    printf("c: %p\n", (void *)&packed.c);

    return 0;
}
