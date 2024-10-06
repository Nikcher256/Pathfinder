#include "../inc/libmx.h"

static int count_substrings(const char *s, char c) {
    int count = 0;
    int in_substring = 0;

    while (*s != '\0') {
        if (*s == c) {
            if (in_substring) {
                in_substring = 0;
            }
        } else {
            if (!in_substring) {
                in_substring = 1;
                count++;
            }
        }
        s++;
    }

    return count;
}

static char *copy_substring(const char *start, size_t length) {
    char *substring = (char *)malloc(length + 1);
    if (substring == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; i++) {
        substring[i] = start[i];
    }
    substring[length] = '\0';

    return substring;
}

char **mx_strsplit(const char *s, char c) {
    if (s == NULL) {
        return NULL;
    }

    int num_substrings = count_substrings(s, c);
    char **result = (char **)malloc((num_substrings + 1) * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    const char *start = s;
    int index = 0;
    while (*s != '\0') {
        if (*s == c) {
            if (s > start) {
                size_t length = s - start;
                result[index] = copy_substring(start, length);
                if (result[index] == NULL) {
                    for (int i = 0; i < index; i++) {
                        free(result[i]);
                    }
                    free(result);
                    return NULL;
                }
                index++;
            }
            start = s + 1;
        }
        s++;
    }

    if (s > start) {
        result[index] = copy_substring(start, s - start);
        if (result[index] == NULL) {
            for (int i = 0; i < index; i++) {
                free(result[i]);
            }
            free(result);
            return NULL;
        }
        index++;
    }

    result[index] = NULL;

    return result;
}
