#include "../inc/libmx.h"

int mx_isspace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f';
}

char *mx_del_extra_spaces(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    const char *start = str;
    while (*start && mx_isspace(*start)) {
        start++;
    }

    if (*start == '\0') {
        char *empty_str = (char *)malloc(1);
        if (empty_str == NULL) {
            return NULL;
        }
        empty_str[0] = '\0';
        return empty_str;
    }

    const char *end = start;
    while (*end) {
        end++;
    }
    end--;
    while (end >= start && mx_isspace(*end)) {
        end--;
    }

    size_t length = (end - start) + 1;

    char *result = (char *)malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    char *dst = result;
    int in_word = 0;

    while (start <= end) {
        if (mx_isspace(*start)) {
            if (in_word) {
                *dst++ = ' ';
                in_word = 0;
            }
        } else {
            *dst++ = *start;
            in_word = 1;
        }
        start++;
    }
    *dst = '\0';

    return result;
}
