#include "../inc/libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    const unsigned char *ptr = s;
    unsigned char uc = (unsigned char)c;

    while (n--) {
        if (*ptr == uc) {
            return (void *)ptr;
        }
        ptr++;
    }
    return NULL;
}
