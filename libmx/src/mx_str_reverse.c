#include "../inc/libmx.h"

void mx_str_reverse(char *s) {
    if (s == NULL) {
        return;
    }

    int left = 0;
    int right = mx_strlen(s) - 1;

    while (left < right) {
        char temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        left++;
        right--;
    }
}
