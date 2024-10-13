#include <malloc.h>  // For malloc_usable_size on Linux different on Mac

#include "../inc/libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    if (size == 0) {
        free(ptr);
        return NULL;
    }

    if (ptr == NULL) {
        return malloc(size);
    }

    size_t old_size = malloc_usable_size(ptr);

    // Allocate new memory block
    void *new_ptr = malloc(size);
    if (new_ptr == NULL) {
        return NULL;
    }

    mx_memcpy(new_ptr, ptr, (old_size < size) ? old_size : size);

    free(ptr);

    return new_ptr;
}
