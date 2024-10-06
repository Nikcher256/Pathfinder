#include "../inc/libmx.h"

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    static struct {
        char leftover[1024];
        size_t len;
        size_t pos;
    } buffer_state = {.len = 0, .pos = 0};

    if (fd < 0 || !lineptr || buf_size <= 0) {
        return -2;
    }

    char *buffer = (char *)malloc(buf_size);
    if (!buffer) {
        return -2;
    }

    size_t total_size = 0;
    size_t capacity = buf_size;
    char *result = (char *)malloc(capacity);
    if (!result) {
        free(buffer);
        return -2;
    }

    ssize_t bytes_read;
    int found_delim = 0;

    while (buffer_state.pos < buffer_state.len) {
        if (buffer_state.leftover[buffer_state.pos] == delim) {
            buffer_state.pos++;
            found_delim = 1;
            break;
        }
        if (total_size >= capacity) {
            capacity *= 2;
            char *new_result = mx_realloc(result, capacity);
            if (!new_result) {
                free(buffer);
                free(result);
                return -2;
            }
            result = new_result;
        }

        result[total_size++] = buffer_state.leftover[buffer_state.pos++];
    }

    while (!found_delim && (bytes_read = read(fd, buffer, buf_size)) > 0) {
        size_t i;
        for (i = 0; i < (size_t)bytes_read; i++) {
            if (buffer[i] == delim) {
                size_t remaining = bytes_read - (i + 1);
                if (remaining > 0) {
                    mx_memset(buffer_state.leftover, 0, sizeof(buffer_state.leftover));
                    mx_memcpy(buffer_state.leftover, buffer + i + 1, remaining);
                    buffer_state.len = remaining;
                    buffer_state.pos = 0;
                } else {
                    buffer_state.len = 0;
                }
                found_delim = 1;
                break;
            }

            if (total_size >= capacity) {
                capacity *= 2;
                char *new_result = mx_realloc(result, capacity);
                if (!new_result) {
                    free(buffer);
                    free(result);
                    return -2;
                }
                result = new_result;
            }

            result[total_size++] = buffer[i];
        }
    }

    free(buffer);

    if (bytes_read == 0 && total_size == 0 && !found_delim) {
        free(result);
        return -1;
    }

    result[total_size] = '\0';
    *lineptr = result;

    if (bytes_read == 0) {
        buffer_state.len = 0;
        buffer_state.pos = 0;
    }

    return total_size;
}
