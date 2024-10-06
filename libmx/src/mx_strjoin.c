#include "../inc/libmx.h"

char *mx_strjoin(const char *s1, const char *s2) {
    if (s1 == NULL && s2 == NULL) {
        return NULL;
    }

    if (s1 == NULL) {
        char *result = (char *)malloc(mx_strlen(s2) + 1);
        if (result == NULL) {
            return NULL;
        }
        return mx_strcpy(result, s2);
    }

    if (s2 == NULL) {
        char *result = (char *)malloc(mx_strlen(s1) + 1);
        if (result == NULL) {
            return NULL;
        }
        return mx_strcpy(result, s1);
    }

    int len1 = mx_strlen(s1);
    int len2 = mx_strlen(s2);
    char *result = (char *)malloc(len1 + len2 + 1);
    if (result == NULL) {
        return NULL;
    }

    mx_strcpy(result, s1);
    mx_strcpy(result + len1, s2);

    return result;
}
