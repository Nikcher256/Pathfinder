#include "../inc/pathfinder.h"
#include "../libmx/inc/libmx.h"

int is_valid_bridge_line(const char *line) {
    char *dash = mx_strchr(line, '-');
    char *comma = mx_strchr(line, ',');

    if (!dash || !comma || dash > comma) {
        return 0;
    }

    if (dash == line || *(dash - 1) == '-' || *(dash + 1) == '-') {
        return 0;
    }

    if (!is_digit_string(comma + 1)) {
        return 0;
    }

    return 1;
}
