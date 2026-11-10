
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(void) {
    const char *filename = "log.txt";

    char input[BUFFER_SIZE];
    char output[BUFFER_SIZE + 64];

    // Open the log file in append mode.
    int fd = open(filename,
                  O_WRONLY | O_CREAT | O_APPEND,
                  0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    printf("Enter log message: ");

    // Read one line from standard input using read().
    ssize_t bytes_read = 0;

    while (bytes_read < BUFFER_SIZE - 1) {
        char ch;

        ssize_t result = read(STDIN_FILENO, &ch, 1);

        if (result == -1) {
            if (errno == EINTR)
                continue;

            perror("read");
            close(fd);
            return 1;
        }

        if (result == 0 || ch == '\n')
            break;

        input[bytes_read++] = ch;
    }

    input[bytes_read] = '\0';

    // Construct the log entry with the process ID.
    int output_length = snprintf(
        output,
        sizeof(output),
        "PID=%ld: %s",
        (long)getpid(),
        input
    );

    if (output_length < 0 ||
        output_length >= (int)sizeof(output)) {
        fprintf(stderr, "Message too long\n");
        close(fd);
        return 1;
    }

    // Append newline if it is not already present.
    if (output_length == 0 ||
        output[output_length - 1] != '\n') {
        output[output_length++] = '\n';
    }

    // Write the complete log entry.
    ssize_t written = 0;

    while (written < output_length) {
        ssize_t result = write(
            fd,
            output + written,
            output_length - written
        );

        if (result == -1) {
            if (errno == EINTR)
                continue;

            perror("write");
            close(fd);
            return 1;
        }

        if (result == 0) {
            fprintf(stderr, "write returned 0\n");
            close(fd);
            return 1;
        }

        written += result;
    }

    // O_APPEND makes each write append at the end.
    // SEEK_CUR reports the current offset after the write.
    // The offset advances as bytes are written, so it grows
    // even though O_APPEND controls the write location.
    off_t final_offset = lseek(fd, 0, SEEK_CUR);

    if (final_offset == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    printf("Final file offset: %lld\n",
           (long long)final_offset);

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}
