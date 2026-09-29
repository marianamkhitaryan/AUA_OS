#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, sum = 0;
    int *array;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of elements must be positive.\n");
        return 1;
    }

    array = malloc(n * sizeof(int));

    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers: ", n);

    for (i = 0; i < n; i++) {
        scanf("%d", &array[i]);
        sum += array[i];
    }

    printf("Sum of the array: %d\n", sum);

    free(array);

    return 0;
}
