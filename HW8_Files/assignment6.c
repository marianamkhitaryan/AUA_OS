
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 4096

// Helper function to write all bytes.
int write_all(int fd, const char *buffer, size_t length) {
    size_t written = 0;

    while (written < length) {
        ssize_t result = write(
            fd,
            buffer + written,
            length - written
        );

        if (result == -1) {
            if (errno == EINTR)
                continue;

            perror("write");
            return -1;
        }

        if (result == 0) {
            fprintf(stderr, "write returned 0\n");
            return -1;
        }

        written += result;
    }

    return 0;
}

int main(void) {
    const char *filename = "numbers.txt";

    // Create or truncate the file.
    int fd = open(filename,
                  O_WRONLY | O_CREAT | O_TRUNC,
                  0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write numbers 1 through 10, one per line.
    for (int i = 1; i <= 10; i++) {
        char line[32];

        int length = snprintf(line, sizeof(line),
                              "%d\n", i);

        if (length < 0 || length >= (int)sizeof(line)) {
            fprintf(stderr, "snprintf failed\n");
            close(fd);
            return 1;
        }

        if (write_all(fd, line, length) == -1) {
            close(fd);
            return 1;
        }
    }

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    // Reopen the file for reading and writing.
    fd = open(filename, O_RDWR);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Scan the file and count newline characters.
    off_t line4_offset = 0;
    int newline_count = 0;
    char ch;

    while (newline_count < 3) {
        ssize_t result = read(fd, &ch, 1);

        if (result == -1) {
            if (errno == EINTR)
                continue;

            perror("read");
            close(fd);
            return 1;
        }

        if (result == 0) {
            fprintf(stderr, "Unexpected EOF\n");
            close(fd);
            return 1;
        }

        if (ch == '\n')
            newline_count++;
    }

    // Current position is the beginning of line 4.
    line4_offset = lseek(fd, 0, SEEK_CUR);

    if (line4_offset == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    printf("Line 4 offset: %lld\n",
           (long long)line4_offset);

    // Determine the remaining file size.
    off_t file_size = lseek(fd, 0, SEEK_END);

    if (file_size == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    off_t remainder_size = file_size - line4_offset;

    // Allocate memory for the remaining content.
    char *remainder = malloc(remainder_size);

    if (remainder == NULL && remainder_size > 0) {
        perror("malloc");
        close(fd);
        return 1;
    }

    // Move back to the start of line 4.
    if (lseek(fd, line4_offset, SEEK_SET) == -1) {
        perror("lseek");
        free(remainder);
        close(fd);
        return 1;
    }

    // Read the remainder of the file.
    size_t total_read = 0;

    while (total_read < (size_t)remainder_size) {
        ssize_t result = read(
            fd,
            remainder + total_read,
            remainder_size - total_read
        );

        if (result == -1) {
            if (errno == EINTR)
                continue;

            perror("read");
            free(remainder);
            close(fd);
            return 1;
        }

        if (result == 0) {
            fprintf(stderr, "Unexpected EOF\n");
            free(remainder);
            close(fd);
            return 1;
        }

        total_read += result;
    }

    // Seek to the beginning of line 4.
    if (lseek(fd, line4_offset, SEEK_SET) == -1) {
        perror("lseek");
        free(remainder);
        close(fd);
        return 1;
    }

    // Overwrite line 4 with 100.
    if (write_all(fd, "100\n", 4) == -1) {
        free(remainder);
        close(fd);
        return 1;
    }

    // Write the saved remainder after the replacement.
    if (write_all(fd, remainder, remainder_size) == -1) {
        free(remainder);
        close(fd);
        return 1;
    }

    free(remainder);

    // Truncate to the correct final length.
    off_t final_size = line4_offset + 4 + remainder_size;

    if (ftruncate(fd, final_size) == -1) {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    // Reopen and print the final file content.
    fd = open(filename, O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buffer[BUFFER_SIZE];

    while (1) {
        ssize_t result = read(fd, buffer, sizeof(buffer));

        if (result == -1) {
            if (errno == EINTR)
                continue;

            perror("read");
            close(fd);
            return 1;
        }

        if (result == 0)
            break;

        if (write_all(STDOUT_FILENO, buffer, result) == -1) {
            close(fd);
            return 1;
        }
    }

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}
