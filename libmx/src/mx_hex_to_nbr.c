#include "../inc/libmx.h"

unsigned long mx_hex_to_nbr(const char *hex) {
    if (hex == NULL) {
        return 0;
    }

    unsigned long result = 0;

    while (*hex) {
        result *= 16;

        if (*hex >= '0' && *hex <= '9') {
            result += *hex - '0';
        } else if (*hex >= 'A' && *hex <= 'F') {
            result += *hex - 'A' + 10;
        } else if (*hex >= 'a' && *hex <= 'f') {
            result += *hex - 'a' + 10;
        } else {
            return 0;
        }

        hex++;
    }

    return result;
}
