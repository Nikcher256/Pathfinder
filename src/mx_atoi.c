#include "../inc/libmx.h"

int mx_atoi(const char *str) {
    int result = 0;
    int sign = 1;
    bool started = false;

    while (*str == ' ') {
        str++;
    }

    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (*str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
        started = true;
    }

    return started ? result * sign : 0;
}
