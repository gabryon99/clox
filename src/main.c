#include <stdio.h>

#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]) {

    Chunk chunk;
    initChunk(&chunk);

    size_t constant = addConstant(&chunk, 3.14);
    writeChunk(&chunk, OP_CONSTANT, 123);
    writeChunk(&chunk, constant, 123);

    writeChunk(&chunk, OP_RETURN, 123);
    disassembleChunk(&chunk, "test-chunk");
    freeChunk(&chunk);

    return 0;
}
