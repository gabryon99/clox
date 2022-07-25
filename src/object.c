#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "loxmemory.h"
#include "object.h"
#include "value.h"
#include "vm.h"
#include "table.h"

#define ALLOCATE_OBJ(type, objectType) \
    (type*)allocateObject(sizeof(type), objectType)

static Obj* allocateObject(size_t size, ObjType type) {

    Obj* object = (Obj*) reallocate(NULL, 0, size);
    object->type = type;

    object->next = vm.objects;
    vm.objects = object;

    return object;
}

static uint32_t hashString(const char* key, int length) {
    // Hash Function: FNV-1a
    uint32_t hash = 2166136261u;
    for (int i = 0; i < length; i++) {
        hash ^= (uint8_t) key[i];
        hash *= 16777619;
    }
    return hash;
}

static uint32_t hashStringConcatenated(const char* k1, const char* k2, int l1, int l2) {
    // Hash Function: FNV-1a
    uint32_t hash = 2166136261u;

    for (int i = 0; i < l1; i++) {
        hash ^= (uint8_t) k1[i];
        hash *= 16777619;
    }

    for (int i = 0; i < l2; i++) {
        hash ^= (uint8_t) k2[i];
        hash *= 16777619;
    }

    return hash;
}

ObjString* makeString(int length, uint32_t hash) {

    ObjString* objString = (ObjString*) allocateObject((sizeof(char) * (length + 1)) + sizeof(ObjString), OBJ_STRING);
    objString->length = length;
    objString->hash = hash;

    tableSet(&vm.strings, objString, NIL_VAL);

    return objString;
}

ObjString* concatenateStrings(const char* s1, const char* s2, int l1, int l2) {

    uint32_t hash = hashStringConcatenated(s1, s2, l1, l2);

    int length = l1 + l2;
    ObjString* result = makeString(length, hash);

    memcpy(result->chars, s1, l1);
    memcpy(result->chars + l1, s2, l2);

    result->chars[length] = '\0';

    return result;
}

ObjString* copyString(const char* chars, int length) {

    uint32_t hash = hashString(chars, length);

    ObjString* interned = tableFindString(&vm.strings, chars, length, hash);
    // String was already created, we retrieve it from the pool.
    if (interned != NULL) {
        return interned;
    }

    ObjString* string = makeString(length, hash);

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