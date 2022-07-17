#include "loxmemory.h"

void* reallocate(void* pointer, size_t oldSize, size_t newSize) {

    if (newSize == 0) {
        free(pointer);
        return NULL;
    }

    void* result = realloc(pointer, newSize);
    if (result == NULL) {
        // Failed memory allocation.
        perror("Run out of memory:");
        exit(EXIT_FAILURE);
    }

    return result;
}