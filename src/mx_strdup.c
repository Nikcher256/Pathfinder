#include "../inc/libmx.h"

char *mx_strdup(const char *s1) {
    if (s1 == NULL) {
        return NULL;
    }

    int length = mx_strlen(s1);
    char *dup = (char *)malloc((length + 1) * sizeof(char));

    if (dup == NULL) {
        return NULL;
    }

    for (int i = 0; i < length; i++) {
        dup[i] = s1[i];
    }
    dup[length] = '\0';

    return dup;
}
