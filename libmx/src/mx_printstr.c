#include "../inc/libmx.h"

void mx_printstr(const char *s) {
    if (s == NULL) {
        return;
    }

    while (*s != '\0') {
        mx_printchar(*s);
        s++;
    }
}
