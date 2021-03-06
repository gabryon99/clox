#include <stdio.h>

#include "debug.h"

size_t constantInstruction(const char *name, const Chunk *chunk, size_t offset);

void disassembleChunk(const Chunk* chunk, const char* msg) {

    fprintf(stdout, "== %s ==\n", msg);
    for (size_t offset = 0; offset < chunk->count; ) {
        offset = disassembleInstruction(chunk, offset);
    }
}

size_t simpleInstruction(const char* name, size_t offset) {
    fprintf(stdout, "%s\n", name);
    return offset + 1;
}

size_t byteInstruction(const char *name, const Chunk *chunk, size_t offset) {
    uint8_t value = chunk->code[offset + 1];
    fprintf(stdout, "%-20s %4d\n", name, value);
    return offset + 2;
}

size_t jumpInstruction(const char *name, int sign, const Chunk *chunk, size_t offset) {
    uint16_t jump = ((chunk->code[offset + 1] << 8) | chunk->code[offset + 2]);
    fprintf(stdout, "%-20s %4zu -> %lu\n", name, offset, offset + 3 + sign * jump);
    return offset + 3;
}

size_t constantInstruction(const char *name, const Chunk *chunk, size_t offset) {
    uint8_t constant = chunk->code[offset + 1];
    fprintf(stdout, "%-20s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    fprintf(stdout, "'\n");
    return offset + 2;
}

size_t constantLongInstruction(const char *name, const Chunk *chunk, size_t offset) {

    // Again, my machine is little endian
    uint32_t constant = (chunk->code[offset + 1]) | (chunk->code[offset + 2] << 8) | (chunk->code[offset + 3] << 16);

    fprintf(stdout, "%-20s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    fprintf(stdout, "'\n");
    return offset + 4;
}

size_t disassembleInstruction(const Chunk* chunk, size_t offset) {

    fprintf(stdout, "%04zu ", offset);

    // Get current instruction line
    size_t line = getLine(chunk, offset);

    if (offset > 0 && line == getLine(chunk, offset - 1)) {
        fprintf(stdout, "\t| ");
    }
    else {
        fprintf(stdout, "%4d ", chunk->lines[offset].line);
    }

    uint8_t instruction = chunk->code[offset];

    switch (instruction) {
        case OP_RETURN: {
            return simpleInstruction("OP_RETURN", offset);
        }
        case OP_CONSTANT: {
            return constantInstruction("OP_CONSTANT", chunk, offset);
        }
        case OP_CONSTANT_LONG: {
            return constantLongInstruction("OP_LONG_CONSTANT", chunk, offset);
        }
        case OP_NEGATE: {
            return simpleInstruction("OP_NEGATE", offset);
        }
        case OP_ADD: {
            return simpleInstruction("OP_ADD", offset);
        }
        case OP_SUBTRACT: {
            return simpleInstruction("OP_SUBTRACT", offset);
        }
        case OP_MULTIPLY: {
            return simpleInstruction("OP_MULTIPLY", offset);
        }
        case OP_DIVIDE: {
            return simpleInstruction("OP_DIVIDE", offset);
        }
        case OP_NIL: {
            return simpleInstruction("OP_NIL", offset);
        }
        case OP_TRUE: {
            return simpleInstruction("OP_TRUE", offset);
        }
        case OP_FALSE: {
            return simpleInstruction("OP_FALSE", offset);
        }
        case OP_NOT: {
            return simpleInstruction("OP_NOT", offset);
        }
        case OP_EQUAL: {
            return simpleInstruction("OP_EQUAL", offset);
        }
        case OP_LESS: {
            return simpleInstruction("OP_LESS", offset);
        }
        case OP_GREATER: {
            return simpleInstruction("OP_GREATER", offset);
        }
        case OP_PRINT: {
            return simpleInstruction("OP_PRINT", offset);
        }
        case OP_POP: {
            return simpleInstruction("OP_POP", offset);
        }
        case OP_POPN: {
            return byteInstruction("OP_POPN", chunk, offset);
        }
        case OP_SET_LOCAL: {
            return byteInstruction("OP_SET_LOCAL", chunk, offset);
        }
        case OP_GET_LOCAL: {
            return byteInstruction("OP_GET_LOCAL", chunk, offset);
        }
        case OP_JUMP_IF_FALSE: {
            return jumpInstruction("OP_JUMP_IF_FALSE", 1, chunk, offset);
        }
        case OP_JUMP: {
            return jumpInstruction("OP_JUMP", 1, chunk, offset);
        }
        case OP_LOOP: {
            return jumpInstruction("OP_LOOP", -1, chunk, offset);
        }
        case OP_DEFINE_GLOBAL: {
            return constantInstruction("OP_DEFINE_GLOBAL", chunk, offset);
        }
        case OP_GET_GLOBAL: {
            return constantInstruction("OP_GET_GLOBAL", chunk, offset);
        }
        case OP_SET_GLOBAL: {
            return constantInstruction("OP_SET_GLOBAL", chunk, offset);
        }
        default: {
            fprintf(stderr, "Unknown opcode %d\n", instruction);
            return offset + 1;
        }
    }
}

void printConstantPool(const Chunk* chunk, const char* msg) {

    fprintf(stdout, "== %s-constant-pool ==\n", msg);

    for (size_t i = 0; i < chunk->constants.count; i++) {
        fprintf(stdout, "%04zu: ", i);
        printValue(chunk->constants.values[i]);
        fprintf(stdout, "\n");
    }

}