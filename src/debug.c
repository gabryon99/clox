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

size_t constantInstruction(const char *name, const Chunk *chunk, size_t offset) {
    uint8_t constant = chunk->code[offset + 1];
    fprintf(stdout, "%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    fprintf(stdout, "'\n");
    return offset + 2;
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
        default: {
            fprintf(stderr, "Unknown opcode %d\n", instruction);
            return offset + 1;
        }
    }
}

