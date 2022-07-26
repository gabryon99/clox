#include "value.h"
#include "loxmemory.h"
#include "object.h"

#include <string.h>

void initValueArray(ValueArray* array) {
    array->capacity = 0;
    array->count = 0;
    array->values = NULL;
}

void writeValueArray(ValueArray* array, Value value) {

    if (array->capacity < array->count + 1) {

        // Increase the chunk's capacity
        size_t oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values = GROW_ARRAY(Value, array->values, oldCapacity, array->capacity);
    }

    array->values[array->count] = value;
    array->count++;
}

void freeValueArray(ValueArray* array) {
    FREE_ARRAY(Value, array->values, array->capacity);
    initValueArray(array);
}

void printValue(Value value) {
    switch (value.type) {
        case VAL_BOOL: {
            fprintf(stdout, AS_BOOL(value) ? "true" : "false");
            break;
        }
        case VAL_NIL: {
            fprintf(stdout, "nil");
            break;
        }
        case VAL_NUMBER: {
            fprintf(stdout, "%g", AS_NUMBER(value));
            break;
        }
        case VAL_OBJ: {
            printObject(value);
            break;
        }
    }
}

bool valuesEqual(Value a, Value b) {
    if (a.type != b.type) {
        return false;
    }
    switch (a.type) {
        case VAL_BOOL: {
            return AS_BOOL(a) == AS_BOOL(b);
        }
        case VAL_NUMBER: {
            return AS_NUMBER(a) == AS_NUMBER(b);
        }
        case VAL_NIL: {
            return true;
        }
        case VAL_OBJ: {
            return AS_OBJ(a) == AS_OBJ(b);
        }
        default: {
            // Unreachable.
            return false;
        }
    }
}


bool checkValue(ValueArray* array, Value value, size_t* loc) {

    for (size_t i = 0; i < array->count; i++) {
        if (valuesEqual(array->values[i], value)) {
            *loc = i;
            return true;
        }
    }

    return false;
}