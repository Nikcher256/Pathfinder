#include "../inc/libmx.h"

void mx_swap(char **s1, char **s2) {
    char *temp = *s1;
    *s1 = *s2;
    *s2 = temp;
}

int mx_bubble_sort(char **arr, int size) {
    if (!arr || size <= 0) {
        return 0;
    }

    int swap_count = 0;
    int swapped;

    for (int i = 0; i < size - 1; i++) {
        swapped = 0;
        for (int j = 0; j < size - i - 1; j++) {
            if (mx_strcmp(arr[j], arr[j + 1]) > 0) {
                mx_swap(&arr[j], &arr[j + 1]);
                swap_count++;
                swapped = 1;
            }
        }
        if (!swapped) {
            break;
        }
    }

    return swap_count;
}
