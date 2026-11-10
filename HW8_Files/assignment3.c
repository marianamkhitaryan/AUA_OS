
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(void) {
    char filename[1024];

    printf("Enter file path: ");

    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        perror("fgets");
        return 1;
    }

    filename[strcspn(filename, "\n")] = '\0';

    int fd = open(filename, O_RDONLY);

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

    for (off_t position = file_size - 1;
         position >= 0;
         position--) {

        if (lseek(fd, position, SEEK_SET) == -1) {
            perror("lseek");
            close(fd);
            return 1;
        }

        char byte;

        ssize_t bytes_read = read(fd, &byte, 1);

        if (bytes_read == -1) {
            perror("read");
            close(fd);
            return 1;
        }

        if (bytes_read != 1) {
            fprintf(stderr, "Unexpected end of file\n");
            close(fd);
            return 1;
        }
        ssize_t result;

        do {
            result = write(STDOUT_FILENO, &byte, 1);
        } while (result == -1 && errno == EINTR);

        if (result == -1) {
            perror("write");
            close(fd);
            return 1;
        }
    }
    if (write(STDOUT_FILENO, "\n", 1) == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    if (close(fd) == -1) {
        perror("close");
        return 1;
    }

    return 0;
}
