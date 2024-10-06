#include "../inc/libmx.h"

void mx_del_strarr(char ***arr) {
    if (arr != NULL && *arr != NULL) {
        char **current = *arr;

        while (*current != NULL) {
            free(*current);
            current++;
        }
        free(*arr);
        *arr = NULL;
    }
}
