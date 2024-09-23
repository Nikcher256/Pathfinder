#include "../inc/libmx.h"

void handle_error(const char* message) {
    write(2, message, mx_strlen(message));
    exit(EXIT_FAILURE);
}
