#ifndef CLOX_VM_H
#define CLOX_VM_H

#include "chunk.h"

#define STACK_SIZE 256

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

typedef struct {
    Chunk*      chunk;
    uint8_t*    ip; // Instruction Pointer
    Value       stack[STACK_SIZE];
    Value*      stackTop;
} VM;

void initVM();
void freeVM();

InterpretResult interpret(Chunk* chunk);
void push(Value value);
Value pop();

#endif //CLOX_VM_H
