#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i;
    int *array;
    double sum = 0, average;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of elements must be positive.\n");
        return 1;
    }

    array = calloc(n, sizeof(int));

    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Array after calloc: ");

    for (i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }

    printf("\n");

    printf("Enter %d integers: ", n);

    for (i = 0; i < n; i++) {
        scanf("%d", &array[i]);
        sum += array[i];
    }

    printf("Updated array: ");

    for (i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }

    average = sum / n;

    printf("\nAverage of the array: %.2f\n", average);

    free(array);

    return 0;
}
