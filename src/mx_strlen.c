#include "../inc/libmx.h"

size_t mx_strlen(const char *s) {
    size_t length = 0;
    while (s[length] != '\0') {
        length++;
    }
    return length;
}
