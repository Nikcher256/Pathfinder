#include "../inc/libmx.h"

int mx_count_words(const char *str, char delimiter) {
    if (str == NULL) {
        return -1;
    }

    int count = 0;
    int in_word = 0;

    while (*str != '\0') {
        if (*str == delimiter) {
            in_word = 0;
        } else if (in_word == 0) {
            count++;
            in_word = 1;
        }
        str++;
    }

    return count;
}
