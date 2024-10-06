#include "../inc/libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    const unsigned char *p = (const unsigned char *)s + n - 1;
    unsigned char uc = (unsigned char)c;

    while (n--) {
        if (*p == uc) {
            return (void *)p;
        }
        p--;
    }

    return NULL;
}
