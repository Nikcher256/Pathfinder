#include "../inc/libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    if (!arr || size <= 0 || !s || !count) {
        return -1;
    }

    int left = 0;
    int right = size - 1;
    *count = 0;

    while (left <= right) {
        (*count)++;
        int mid = left + (right - left) / 2;
        int cmp = mx_strcmp(arr[mid], s);

        if (cmp == 0) {
            return mid;
        } else if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    *count = 0;
    return -1;
}
