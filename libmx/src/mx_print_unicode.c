#include "../inc/libmx.h"

void mx_print_unicode(wchar_t c) {
    char buffer[4];
    int length;

    if (c <= 0x7F) {
        buffer[0] = (char)c;
        length = 1;
    } else if (c <= 0x7FF) {
        buffer[0] = 0xC0 | (c >> 6);
        buffer[1] = 0x80 | (c & 0x3F);
        length = 2;
    } else if (c <= 0xFFFF) {
        buffer[0] = 0xE0 | (c >> 12);
        buffer[1] = 0x80 | ((c >> 6) & 0x3F);
        buffer[2] = 0x80 | (c & 0x3F);
        length = 3;
    } else if (c <= 0x10FFFF) {
        buffer[0] = 0xF0 | (c >> 18);
        buffer[1] = 0x80 | ((c >> 12) & 0x3F);
        buffer[2] = 0x80 | ((c >> 6) & 0x3F);
        buffer[3] = 0x80 | (c & 0x3F);
        length = 4;
    } else {
        return;
    }

    write(1, buffer, length);
}
