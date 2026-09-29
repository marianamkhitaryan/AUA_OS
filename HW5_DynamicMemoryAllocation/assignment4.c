#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 50

int main() {
    int i;
    char **strings;

    strings = malloc(3 * sizeof(char *));

    if (strings == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < 3; i++) {
        strings[i] = malloc((MAX_LENGTH + 1) * sizeof(char));

        if (strings[i] == NULL) {
            printf("Memory allocation failed.\n");

            while (i > 0) {
                free(strings[i - 1]);
                i--;
            }

            free(strings);
            return 1;
        }
    }

    printf("Enter 3 strings:\n");

    for (i = 0; i < 3; i++) {
        fgets(strings[i], MAX_LENGTH + 1, stdin);
        strings[i][strcspn(strings[i], "\n")] = '\0';
    }

    char **temp = realloc(strings, 5 * sizeof(char *));

    if (temp == NULL) {
        printf("Memory reallocation failed.\n");

        for (i = 0; i < 3; i++) {
            free(strings[i]);
        }

        free(strings);
        return 1;
    }

    strings = temp;

    for (i = 3; i < 5; i++) {
        strings[i] = malloc((MAX_LENGTH + 1) * sizeof(char));

        if (strings[i] == NULL) {
            printf("Memory allocation failed.\n");

            for (int j = 0; j < i; j++) {
                free(strings[j]);
            }

            free(strings);
            return 1;
        }
    }

    printf("Enter 2 more strings:\n");

    for (i = 3; i < 5; i++) {
        fgets(strings[i], MAX_LENGTH + 1, stdin);
        strings[i][strcspn(strings[i], "\n")] = '\0';
    }

    printf("All strings: ");

    for (i = 0; i < 5; i++) {
        printf("%s", strings[i]);

        if (i < 4) {
            printf(" ");
        }
    }

    printf("\n");

    for (i = 0; i < 5; i++) {
        free(strings[i]);
    }

    free(strings);

    return 0;
}
