#include "../inc/libmx.h"

bool is_digit_string(const char *str) {
    if (!str || *str == '\0') return false;

    while (*str) {
        if (*str < '0' || *str > '9') {
            return false;
        }
        str++;
    }
    return true;
}
