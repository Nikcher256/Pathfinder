#include "../inc/libmx.h"

void mx_printint(int n) {
    if (n == 0) {
        write(1, "0", 1);
        return;
    }

    if (n < 0) {
        write(1, "-", 1);
        n = -n;
    }

    char buffer[12];  // Enough space to hold an int as a string
    int i = 0;

    while (n > 0) {
        buffer[i++] = (n % 10) + '0';  // Convert last digit to char
        n /= 10;
    }

    // Print the digits in reverse
    while (--i >= 0) {
        write(1, &buffer[i], 1);
    }
}
