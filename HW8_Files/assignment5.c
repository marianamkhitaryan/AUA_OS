
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(void) {
    const char *filename = "sparse.bin";

    // Create or truncate the sparse file.
    int fd = open(filename,
                  O_WRONLY | O_CREAT | O_TRUNC,
                  0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Write START.
    const char *start = "START";
    size_t start_length = 5;
    size_t written = 0;

    while (written < start_length) {
        ssize_t result = write(
            fd,
            start + written,
            start_length - written
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

    // Skip forward by 1 MiB from the current position.
    if (lseek(fd, 1024 * 1024, SEEK_CUR) == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    // Write END at the new position.
    const char *end = "END";
    size_t end_length = 3;
    written = 0;

    while (written < end_length) {
        ssize_t result = write(
            fd,
            end + written,
            end_length - written
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

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    // Reopen the file to verify its apparent size.
    fd = open(filename, O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    off_t file_size = lseek(fd, 0, SEEK_END);

    if (file_size == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    printf("Apparent file size: %lld bytes\n",
           (long long)file_size);

    // The skipped region is a hole: the filesystem can represent
    // it without allocating blocks for all those zero bytes.
    // Therefore, disk usage reported by du can be much smaller
    // than the apparent file size.

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}
