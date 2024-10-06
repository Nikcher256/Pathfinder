#include "../inc/libmx.h"

int mx_get_char_index(const char *str, char c) {
    if (str == NULL) {
        return -2;
    }

    int len = mx_strlen(str);
    if (len == -1) {
        return -2;
    }

    for (int i = 0; i < len; i++) {
        if (str[i] == c) {
            return i;
        }
    }

    return -1;
}
