#include "../inc/libmx.h"

char *mx_itoa(int number) {
    if (number == 0) {
        char *str = (char *)malloc(2);
        if (!str) return NULL;
        str[0] = '0';
        str[1] = '\0';
        return str;
    }

    int length = 0;
    int temp = number;
    if (temp < 0) {
        length++;
        temp = -temp;
    }
    while (temp != 0) {
        length++;
        temp /= 10;
    }

    char *str = (char *)malloc(length + 1);
    if (!str) return NULL;

    str[length] = '\0';

    if (number < 0) {
        str[0] = '-';
        number = -number;
    }

    while (length > (number <= 0 ? 1 : 0)) {
        str[--length] = (number % 10) + '0';
        number /= 10;
    }

    return str;
}
