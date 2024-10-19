#include "../inc/pathfinder.h"
#include "../libmx/inc/libmx.h"

int is_alpha_string(const char *str) {
    while (*str) {
        if (!mx_isalpha(*str)) {
            return 0;  // Non-alphabetic character found
        }
        str++;
    }
    return 1;  // All characters are alphabetic
}

// Function to check if the island names are valid
int is_valid_island_name(const char *name) { return name && *name && is_alpha_string(name); }

int is_valid_bridge_line(const char *line) {
    char *dash = mx_strchr(line, '-');
    char *comma = mx_strchr(line, ',');

    // Check if dash and comma are found and in the correct order
    if (!dash || !comma || dash > comma) {
        return 0;
    }

    // Extract island names
    size_t island1_length = dash - line;
    size_t island2_length = comma - (dash + 1);

    char island1[island1_length + 1];
    char island2[island2_length + 1];

    mx_strncpy(island1, line, island1_length);
    island1[island1_length] = '\0';  // Null-terminate the string

    mx_strncpy(island2, dash + 1, island2_length);
    island2[island2_length] = '\0';  // Null-terminate the string

    // Check if island names are valid
    if (!is_valid_island_name(island1) || !is_valid_island_name(island2)) {
        return 0;  // Invalid island names
    }

    // Check if there are adjacent dashes
    if (dash == line || *(dash - 1) == '-' || *(dash + 1) == '-') {
        return 0;
    }

    // Check if the distance is valid
    if (!is_digit_string(comma + 1)) {
        return 0;  // Invalid distance
    }

    return 1;  // Valid bridge line
}
