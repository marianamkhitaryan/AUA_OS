#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i;
    int *grades;
    int highest, lowest;

    printf("Enter the number of students: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of students must be positive.\n");
        return 1;
    }

    grades = malloc(n * sizeof(int));

    if (grades == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the grades: ");

    for (i = 0; i < n; i++) {
        scanf("%d", &grades[i]);
    }

    highest = grades[0];
    lowest = grades[0];

    for (i = 1; i < n; i++) {
        if (grades[i] > highest) {
            highest = grades[i];
        }

        if (grades[i] < lowest) {
            lowest = grades[i];
        }
    }

    printf("Highest grade: %d\n", highest);
    printf("Lowest grade: %d\n", lowest);

    free(grades);

    return 0;
}
