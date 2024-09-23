#include "../inc/libmx.h"

int get_next_line(char **content, char **line) {
    if (!*content || !**content) return 0;

    char *newline = mx_strchr(*content, '\n');
    if (newline) {
        *newline = '\0';
        *line = *content;
        *content = newline + 1;
    } else {
        *line = *content;
        *content = NULL;
    }

    return 1;
}
