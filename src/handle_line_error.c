#include "../inc/pathfinder.h"
#include "../libmx/inc/libmx.h"

void handle_line_error(const char *message, int line) {
    const char *error_prefix = "error: line ";
    const char *newline = "\n";

    char *line_str = mx_itoa(line);
    int line_length = mx_strlen(line_str);

    int total_length =
        mx_strlen(error_prefix) + mx_strlen(message) + line_length + mx_strlen(newline);

    char *error_message = malloc(total_length + 1);
    if (!error_message) {
        free(line_str);
        exit(EXIT_FAILURE);
    }

    mx_strcpy(error_message, error_prefix);
    mx_strcat(error_message, line_str);
    mx_strcat(error_message, message);
    mx_strcat(error_message, newline);

    write(STDERR_FILENO, error_message, total_length);

    free(error_message);
    free(line_str);

    exit(EXIT_FAILURE);
}
