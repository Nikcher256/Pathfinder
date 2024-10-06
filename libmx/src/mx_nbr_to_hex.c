#include "../inc/libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    if (nbr == 0) {
        char *result = malloc(2);
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    unsigned long temp = nbr;
    int length = 0;
    while (temp != 0) {
        temp /= 16;
        length++;
    }

    char *hex_str = malloc(length + 1);
    if (!hex_str) {
        return NULL;
    }

    hex_str[length] = '\0';

    while (nbr != 0) {
        unsigned long remain = nbr % 16;
        if (remain < 10) {
            hex_str[--length] = '0' + remain;
        } else {
            hex_str[--length] = 'a' + (remain - 10);
        }
        nbr /= 16;
    }

    return hex_str;
}
