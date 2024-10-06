#include <string.h>

#include "../inc/libmx.h"

static int partition(char **arr, int left, int right);
static void swap(char **arr, int i, int j);
static int count_swaps = 0;

int mx_quicksort(char **arr, int left, int right) {
    if (arr == NULL) {
        return -1;
    }

    if (left < right) {
        int pivotIndex = partition(arr, left, right);
        mx_quicksort(arr, left, pivotIndex - 1);
        mx_quicksort(arr, pivotIndex + 1, right);
    }

    return count_swaps;
}

static int partition(char **arr, int left, int right) {
    int pivotIndex = left + (right - left) / 2;
    char *pivotValue = arr[pivotIndex];
    swap(arr, pivotIndex, right);
    int storeIndex = left;

    for (int i = left; i < right; i++) {
        if (mx_strlen(arr[i]) < mx_strlen(pivotValue)) {
            swap(arr, i, storeIndex);
            storeIndex++;
        }
    }

    swap(arr, storeIndex, right);
    count_swaps++;

    return storeIndex;
}

static void swap(char **arr, int i, int j) {
    char *temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
