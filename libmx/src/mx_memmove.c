#include "../inc/libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
    unsigned char *d = dst;
    const unsigned char *s = src;

    if (d == s) {
        return dst;
    }

    if (d < s || d >= s + len) {
        while (len--) {
            *d++ = *s++;
        }
    } else {
        d += len;
        s += len;
        while (len--) {
            *(--d) = *(--s);
        }
    }

    return dst;
}
