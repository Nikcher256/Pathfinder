#include "../inc/libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
    unsigned char *d = dst;
    const unsigned char *s = src;
    unsigned char uc = (unsigned char)c;

    while (n--) {
        *d = *s;
        if (*s == uc) {
            return (d + 1);
        }
        d++;
        s++;
    }

    return NULL;
}
