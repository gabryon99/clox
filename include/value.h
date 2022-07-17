#ifndef CLOX_VALUE_H
#define CLOX_VALUE_H

#include "common.h"

typedef double Value;

// This is our temporarily constant pool (à-la-Java)
typedef struct {
    size_t count;
    size_t capacity;
    Value* values;
} ValueArray;

/***
 * Initialize constant pool to hold values.
 * @param array
 */
void initValueArray(ValueArray* array);

/***
 * Write a new constant inside the constant pool.
 * @param array
 * @param value
 */
void writeValueArray(ValueArray* array, Value value);

/***
 * Free the memory destroying the constant pool.
 * @param array
 */
void freeValueArray(ValueArray* array);

/***
 * Pretty print a constant value.
 * @param value
 */
void printValue(Value value);

#endif //CLOX_VALUE_H
