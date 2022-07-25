#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "loxmemory.h"
#include "object.h"
#include "value.h"
#include "vm.h"

#define ALLOCATE_OBJ(type, objectType) \
    (type*)allocateObject(sizeof(type), objectType)

static Obj* allocateObject(size_t size, ObjType type) {

    Obj* object = (Obj*) reallocate(NULL, 0, size);
    object->type = type;

    object->next = vm.objects;
    vm.objects = object;

    return object;
}

ObjString* makeString(int length) {
    ObjString* objString = (ObjString*) allocateObject((sizeof(char) * (length + 1)) + sizeof(ObjString), OBJ_STRING);
    objString->length = length;
    return objString;
}

ObjString* copyString(const char* chars, int length) {
    ObjString* string = makeString(length);
    memcpy(string->chars, chars, length);
    string->chars[length] = '\0';
    return string;
}

void printObject(Value value) {
    switch (OBJ_TYPE(value)) {
        case OBJ_STRING: {
            fprintf(stdout, "%s", AS_CSTRING(value));
            break;
        }
    }
}