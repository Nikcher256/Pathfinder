#include "../inc/libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    if (!str || !sub || !replace) {
        return NULL;
    }

    int sub_len = mx_strlen(sub);
    int replace_len = mx_strlen(replace);
    int count = mx_count_substr(str, sub);

    if (count == -1) {
        return NULL;
    }

    if (sub_len == 0) {
        return NULL;
    }

    int new_size = mx_strlen(str) + (replace_len - sub_len) * count + 1;
    char *result = (char *)malloc(new_size);
    if (!result) {
        return NULL;
    }

    char *current_pos = result;
    const char *next_sub_pos;

    while ((next_sub_pos = mx_strstr(str, sub)) != NULL) {
        int copy_len = next_sub_pos - str;
        for (int i = 0; i < copy_len; i++) {
            current_pos[i] = str[i];
        }
        current_pos += copy_len;

        for (int i = 0; i < replace_len; i++) {
            current_pos[i] = replace[i];
        }
        current_pos += replace_len;

        str = next_sub_pos + sub_len;
    }

    while (*str) {
        *current_pos++ = *str++;
    }

    *current_pos = '\0';

    return result;
}
