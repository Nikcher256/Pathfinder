#include "../inc/libmx.h"

char *mx_strncpy(char *dst, const char *src, int len) {
    int i = 0;

    while (i < len && src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }

    while (i < len) {
        dst[i] = '\0';
        i++;
    }

    return dst;
}
