#include "../inc/libmx.h"

char *mx_strcat(char *dst, const char *src) {
    char *dest = dst;

    while (*dest) {
        dest++;
    }

    while (*src) {
        *dest++ = *src++;
    }

    *dest = '\0';

    return dst;
}
