#include "../inc/libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    if (str == NULL || sub == NULL) {
        return -1;
    }
    if (*sub == '\0') {
        return 0;
    }

    int count = 0;
    char *pos = (char *)str;

    while ((pos = mx_strstr(pos, sub)) != NULL) {
        count++;
        pos++;
    }

    return count;
}
