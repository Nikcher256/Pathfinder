#include "../inc/libmx.h"

int mx_isspace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f';
}

const char *mx_ltrim(const char *str) {
    while (*str != '\0' && mx_isspace(*str)) {
        str++;
    }
    return str;
}

const char *mx_rtrim(const char *str) {
    const char *end = str;
    while (*end != '\0') {
        end++;
    }
    end--;

    while (end >= str && mx_isspace(*end)) {
        end--;
    }

    return end;
}

char *mx_strtrim(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    const char *start = mx_ltrim(str);
    if (*start == '\0') {
        char *empty_str = (char *)malloc(1);
        if (empty_str == NULL) {
            return NULL;
        }
        empty_str[0] = '\0';
        return empty_str;
    }

    const char *end = mx_rtrim(start);

    size_t length = end - start + 1;
    char *trimmed_str = (char *)malloc(length + 1);
    if (trimmed_str == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; i++) {
        trimmed_str[i] = start[i];
    }
    trimmed_str[length] = '\0';

    return trimmed_str;
}
