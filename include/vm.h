#ifndef CLOX_VM_H
#define CLOX_VM_H

#include "chunk.h"
#include "table.h"

#define INITIAL_STACK_SIZE 512

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

typedef struct {
    Chunk*      chunk;
    uint8_t*    ip;         // Instruction Pointer
    Value       stack[INITIAL_STACK_SIZE];
    Value*      stackTop;
    Obj*        objects;
    Table       strings;
} VM;

extern VM vm;

void initVM();
void freeVM();

InterpretResult interpret(const char* source);

void push(Value value);
Value pop();

#endif //CLOX_VM_H
