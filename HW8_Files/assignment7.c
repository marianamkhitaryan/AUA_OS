
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 4096

int main(void) {
    char file1[1024];
    char file2[1024];

    // Prompt for the first file path.
    printf("Enter first file path: ");

    if (scanf("%1023s", file1) != 1) {
        fprintf(stderr, "Invalid first file path\n");
        return 1;
    }

    // Prompt for the second file path.
    printf("Enter second file path: ");

    if (scanf("%1023s", file2) != 1) {
        fprintf(stderr, "Invalid second file path\n");
        return 1;
    }

    // Open both files for reading.
    int fd1 = open(file1, O_RDONLY);

    if (fd1 == -1) {
        perror("open first file");
        return 1;
    }

    int fd2 = open(file2, O_RDONLY);

    if (fd2 == -1) {
        perror("open second file");
        close(fd1);
        return 1;
    }

    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];

    long long byte_index = 0;

    while (1) {
        ssize_t bytes1;
        ssize_t bytes2;

        // Read a chunk from the first file.
        do {
            bytes1 = read(fd1, buffer1, BUFFER_SIZE);
        } while (bytes1 == -1 && errno == EINTR);

        if (bytes1 == -1) {
            perror("read first file");
            close(fd1);
            close(fd2);
            return 1;
        }

        // Read a chunk from the second file.
        do {
            bytes2 = read(fd2, buffer2, BUFFER_SIZE);
        } while (bytes2 == -1 && errno == EINTR);

        if (bytes2 == -1) {
            perror("read second file");
            close(fd1);
            close(fd2);
            return 1;
        }

        // Compare all bytes in the common part.
        ssize_t common_length =
            bytes1 < bytes2 ? bytes1 : bytes2;

        for (ssize_t i = 0; i < common_length; i++) {
            if (buffer1[i] != buffer2[i]) {
                printf("Files differ at byte %lld\n",
                       byte_index + i);

                close(fd1);
                close(fd2);

                return 1;
            }
        }

        byte_index += common_length;

        // If the chunks have different lengths,
        // one file ended before the other.
        if (bytes1 != bytes2) {
            printf("Files differ at byte %lld\n",
                   byte_index);

            close(fd1);
            close(fd2);

            return 1;
        }

        // Both files reached EOF at the same position.
        if (bytes1 == 0 && bytes2 == 0) {
            printf("Files are identical\n");

            if (close(fd1) == -1) {
                perror("close first file");
                close(fd2);
                return 1;
            }

            if (close(fd2) == -1) {
                perror("close second file");
                return 1;
            }

            return 0;
        }
    }
}
