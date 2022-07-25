#include "loxmemory.h"
#include "vm.h"
#include "object.h"

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

static void freeObject(Obj* object) {
    switch (object->type) {
        case OBJ_STRING: {
            ObjString* string = (ObjString*)object;
            reallocate(string, sizeof(ObjString) + string->length + 1, 0);
            break;
        }
    }
}

void freeObjects() {
    Obj* object = vm.objects;
    while (object != NULL) {
        Obj* next = object->next;
        freeObject(object);
        object = next;
    }
}