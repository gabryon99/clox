#include <stdio.h>

#include "chunk.h"
#include "debug.h"

int main(int argc, const char* argv[]) {

    Chunk chunk;
    initChunk(&chunk);

    writeChunk(&chunk, OP_RETURN, 123);

    disassembleChunk(&chunk, "test-chunk");
    printConstantPool(&chunk, "test-chunk");

    freeChunk(&chunk);

    return 0;
}
