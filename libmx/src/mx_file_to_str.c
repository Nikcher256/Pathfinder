#include "../inc/libmx.h"

char *mx_file_to_str(const char *file) {
    if (file == NULL) {
        return NULL;
    }

    int fd = open(file, O_RDONLY);
    if (fd < 0) {
        return NULL;
    }

    size_t file_size = 0;
    char buffer[4096];
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        file_size += bytes_read;
    }

    if (bytes_read < 0) {
        close(fd);
        return NULL;
    }

    char *content = (char *)malloc(file_size + 1);
    if (content == NULL) {
        close(fd);
        return NULL;
    }

    int fd2 = open(file, O_RDONLY);
    if (fd2 < 0) {
        free(content);
        close(fd);
        return NULL;
    }

    size_t total_read = 0;
    while ((bytes_read = read(fd2, content + total_read, file_size - total_read)) > 0) {
        total_read += bytes_read;
    }

    if (bytes_read < 0) {
        free(content);
        close(fd);
        close(fd2);
        return NULL;
    }

    content[file_size] = '\0';

    close(fd);
    close(fd2);

    return content;
}
