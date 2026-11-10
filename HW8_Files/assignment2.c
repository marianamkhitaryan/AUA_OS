
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    const char *filename = "data.txt";
    const char *text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    size_t length = 26;
    size_t written = 0;

    while (written < length) {
        ssize_t result = write(fd, text + written, length - written);

        if (result == -1) {
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

    fd = open(filename, O_RDWR);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    off_t original_size = lseek(fd, 0, SEEK_END);

    if (original_size == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    printf("Current size: %lld bytes\n",
           (long long)original_size);

    if (ftruncate(fd, 10) == -1) {
        perror("ftruncate");
        close(fd);
        return 1;
    }

    off_t new_size = lseek(fd, 0, SEEK_END);

    if (new_size == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    printf("New size: %lld bytes\n",
           (long long)new_size);

    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    char buffer[11];
    ssize_t bytes_read = read(fd, buffer, 10);

    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    buffer[bytes_read] = '\0';

    printf("Remaining content: %s\n", buffer);

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}
