#include <stdio.h>

#include "vm.h"
#include "debug.h"
#include "compiler.h"

// Declare the Virtual Machine as static
VM vm;

static InterpretResult run() {

#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define READ_LONG_CONSTANT() \
    (vm.chunk->constants.values[(READ_BYTE()) | (READ_BYTE() < 8) | (READ_BYTE() < 16)])

#define BINARY_OP(op) \
    do {              \
        double b = pop(); \
        double a = pop(); \
        push(a op b);     \
    } while (false)

    for (;;) {

#ifdef DEBUG_TRACE_EXECUTION

        fprintf(stdout, "\t\t\t\t");
        for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
            fprintf(stdout, "[ ");
            printValue(*slot);
            fprintf(stdout, " ]");
        }
        fprintf(stdout, "\n");

        disassembleInstruction(vm.chunk, (size_t)(vm.ip - vm.chunk->code));
#endif

        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_RETURN: {
                printValue(pop());
                fprintf(stdout, "\n");
                return INTERPRET_OK;
            }
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_CONSTANT_LONG: {
                Value constant = READ_LONG_CONSTANT();
                push(constant);
                break;
            }
            case OP_NEGATE: {
                push(-pop());
                break;
            }
            case OP_ADD: {
                BINARY_OP(+);
                break;
            }
            case OP_SUBTRACT: {
                BINARY_OP(-);
                break;
            }
            case OP_MULTIPLY: {
                BINARY_OP(*);
                break;
            }
            case OP_DIVIDE: {
                BINARY_OP(/);
                break;
            }
        }
    }

#undef READ_BYTE
#undef READ_CONSTANT
#undef READ_LONG_CONSTANT
#undef BINARY_OP
}

static void resetStack() {
    vm.stackTop = vm.stack;
}

void initVM() {
    resetStack();
}

void freeVM() {
    // ...
}

InterpretResult interpret(const char* source) {
    compile(source);
    return INTERPRET_OK;
}

void push(Value value) {
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop() {
    vm.stackTop--;
    return *vm.stackTop;
}