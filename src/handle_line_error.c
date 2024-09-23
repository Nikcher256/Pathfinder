#include "../inc/libmx.h"

void handle_line_error(const char *message, int line) {
    const char *error_prefix = "error: line ";
    const char *newline = "\n";

    int total_length = mx_strlen(error_prefix) + mx_strlen(message);
    total_length += mx_strlen(mx_itoa(line)) + 3;
    total_length += 1;

    char *error_message = malloc(total_length);
    if (!error_message) {
        exit(EXIT_FAILURE);
    }

    mx_strcpy(error_message, error_prefix);

    mx_strcat(error_message, mx_itoa(line));
    mx_strcat(error_message, message);
    mx_strcat(error_message, newline);

    write(STDERR_FILENO, error_message, total_length);

    free(error_message);
    exit(EXIT_FAILURE);
}
