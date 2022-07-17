#include <stdio.h>

#include "debug.h"

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

size_t disassembleInstruction(const Chunk* chunk, size_t offset) {

    fprintf(stdout, "%04zu ", offset);

    uint8_t instruction = chunk->code[offset];

    switch (instruction) {
        case OP_RETURN: {
            return simpleInstruction("OP_RETURN", offset);
        }
        default: {
            fprintf(stderr, "Unknown opcode %d\n", instruction);
            return offset + 1;
        }
    }
}
