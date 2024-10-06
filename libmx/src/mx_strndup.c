#include "../inc/libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    if (s1 == NULL) {
        return NULL;
    }

    size_t length = mx_strlen(s1);
    if (n > length) {
        n = length;
    }

    char *dup = (char *)malloc((n + 1) * sizeof(char));
    if (dup == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < n; i++) {
        dup[i] = s1[i];
    }
    dup[n] = '\0';

    return dup;
}
