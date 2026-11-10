
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 4096

int main(void) {
    char src_path[1024];
    char dest_path[1024];
    char buffer[BUFFER_SIZE];

    printf("Enter source file path: ");
    if (fgets(src_path, sizeof(src_path), stdin) == NULL) {
        perror("fgets");
        return 1;
    }

    src_path[strcspn(src_path, "\n")] = '\0';

    printf("Enter destination file path: ");
    if (fgets(dest_path, sizeof(dest_path), stdin) == NULL) {
        perror("fgets");
        return 1;
    }

    dest_path[strcspn(dest_path, "\n")] = '\0';

    int src_fd = open(src_path, O_RDONLY);
    if (src_fd == -1) {
        perror("open source");
        return 1;
    }

    int dest_fd = open(dest_path,
                       O_WRONLY | O_CREAT | O_TRUNC,
                       0644);

    if (dest_fd == -1) {
        perror("open destination");
        close(src_fd);
        return 1;
    }

    ssize_t bytes_read;
    long long total_bytes = 0;

    while (1) {
        bytes_read = read(src_fd, buffer, sizeof(buffer));

        if (bytes_read == -1) {
            if (errno == EINTR)
                continue;

            perror("read");
            close(src_fd);
            close(dest_fd);
            return 1;
        }

        if (bytes_read == 0)
            break;

        ssize_t written = 0;

        while (written < bytes_read) {
            ssize_t result = write(
                dest_fd,
                buffer + written,
                bytes_read - written
            );

            if (result == -1) {
                if (errno == EINTR)
                    continue;

                perror("write");
                close(src_fd);
                close(dest_fd);
                return 1;
            }

            if (result == 0) {
                fprintf(stderr, "write returned 0\n");
                close(src_fd);
                close(dest_fd);
                return 1;
            }

            written += result;
        }

        total_bytes += bytes_read;
    }

    if (close(src_fd) == -1) {
        perror("close source");
        close(dest_fd);
        return 1;
    }

    if (close(dest_fd) == -1) {
        perror("close destination");
        return 1;
    }

    printf("Total bytes copied: %lld\n", total_bytes);

    return 0;
}
