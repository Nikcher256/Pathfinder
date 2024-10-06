#include "../inc/pathfinder.h"
#include "../libmx/inc/libmx.h"

void handle_file_error(const char *message, const char *filename) {
    const char *error_prefix = "error: file ";
    const char *newline = "\n";

    int total_length = mx_strlen(error_prefix) + mx_strlen(message);
    if (filename) {
        total_length += mx_strlen(filename);
    }
    total_length += mx_strlen(newline);

    char *error_message = malloc(total_length + 1);
    if (!error_message) {
        exit(EXIT_FAILURE);
    }

    mx_strcpy(error_message, error_prefix);
    if (filename) {
        mx_strcat(error_message, filename);
    }
    mx_strcat(error_message, message);
    mx_strcat(error_message, newline);

    write(STDERR_FILENO, error_message, total_length);

    free(error_message);
    exit(EXIT_FAILURE);
}
