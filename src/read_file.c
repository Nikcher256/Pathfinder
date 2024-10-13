#include "../inc/pathfinder.h"
#include "../libmx/inc/libmx.h"

int read_file(const char *filename, char **content, Graph *graph) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        free_graph(graph, 0);
        handle_file_error(" does not exist", filename);
    }

    char buffer[BUFFER_SIZE];
    size_t total_size = 0;
    ssize_t bytes_read;

    *content = malloc(BUFFER_SIZE);
    if (!(*content)) {
        close(fd);
        handle_error("memory allocation error\n");
    }

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        char *new_content = mx_realloc(*content, total_size + bytes_read + 1);
        if (!new_content) {
            free(*content);
            close(fd);
            handle_error("memory reallocation error\n");
        }
        *content = new_content;
        for (ssize_t i = 0; i < bytes_read; i++) {
            (*content)[total_size + i] = buffer[i];
        }
        total_size += bytes_read;
    }

    if (bytes_read < 0) {
        free(*content);
        close(fd);
        handle_error("file reading error\n");
    }

    (*content)[total_size] = '\0';
    close(fd);

    return total_size;
}
