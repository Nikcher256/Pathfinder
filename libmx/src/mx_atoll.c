#include "../inc/libmx.h"

long long mx_atoll(const char *str) {
    // if (mx_strlen(str) > 9) {
    //     return -1;
    // }
    long long result = 0;
    bool is_negative = false;

    while (*str == ' ') str++;

    if (*str == '-') {
        is_negative = true;
        str++;
    } else if (*str == '+') {
        str++;
    }

    while (*str >= '0' && *str <= '9') {
        if (result > (LLONG_MAX - (*str - '0')) / 10) {
            return (is_negative ? LLONG_MIN : LLONG_MAX);
        }
        result = result * 10 + (*str - '0');
        str++;
    }

    return is_negative ? -result : result;
}
