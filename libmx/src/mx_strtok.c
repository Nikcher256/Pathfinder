#include "../inc/libmx.h"

char *mx_strtok(char *str, const char *delim) {
    static char *saved_str = NULL;  // Static variable to hold the state between calls
    char *token;

    // Initialize saved_str if str is provided
    if (str != NULL) {
        saved_str = str;
    }

    // Check if there are no more tokens
    if (saved_str == NULL) {
        return NULL;
    }

    // Skip leading delimiters
    while (*saved_str && strchr(delim, *saved_str)) {
        saved_str++;
    }

    // If we reached the end of the string, return NULL
    if (*saved_str == '\0') {
        saved_str = NULL;
        return NULL;
    }

    // Find the end of the token
    token = saved_str;
    while (*saved_str && !strchr(delim, *saved_str)) {
        saved_str++;
    }

    // Null-terminate the token
    if (*saved_str) {
        *saved_str++ =
            '\0';  // Replace delimiter with null terminator and move to the next character
    }

    return token;  // Return the token
}
