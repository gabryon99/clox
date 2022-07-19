#ifndef CLOX_VALUE_H
#define CLOX_VALUE_H

#include "common.h"

#define BOOL_VAL(value)     ((Value){VAL_BOOL,      {.boolean = value}})
#define NIL_VAL             ((Value){VAL_NIL,       {.number = 0}})
#define NUMBER_VAL(value)   ((Value){VAL_NUMBER,    {.number = value}})

#define IS_BOOL(value)      ((value).type == VAL_BOOL)
#define IS_NIL(value)       ((value).type == VAL_NIL)
#define IS_NUMBER(value)    ((value).type == VAL_NUMBER)

#define AS_BOOL(value)      ((value).as.boolean)
#define AS_NUMBER(value)    ((value).as.number)

typedef enum {
    VAL_BOOL,
    VAL_NIL,
    VAL_NUMBER,
} ValueType;

typedef struct {
    ValueType type; // Type Tag
    // Tagged Union
    union {
        bool boolean;
        double number;
    } as;
} Value;

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

bool valuesEqual(Value a, Value b);

#endif //CLOX_VALUE_H
