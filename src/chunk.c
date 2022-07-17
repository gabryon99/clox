#include <stdlib.h>

#include "chunk.h"
#include "loxmemory.h"

void initChunk(Chunk* chunk) {
    chunk->capacity = 0;
    chunk->count = 0;
    chunk->lineCapacity = 0;
    chunk->lineCount = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {

    // Does the chunk contain enough space?
    if (chunk->capacity < chunk->count + 1) {

        // Increase the chunk's capacity
        size_t oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    }

    // Write the byte inside the chunk and increase the number of bytes
    // written so far.
    chunk->code[chunk->count] = byte;
    chunk->count++;

    if (chunk->lineCapacity < chunk->lineCount + 1) {
        size_t oldCapacity = chunk->lineCapacity;
        chunk->lineCapacity = GROW_CAPACITY(oldCapacity);
        chunk->lines = GROW_ARRAY(LineStart, chunk->lines, oldCapacity, chunk->lineCapacity);
    }

    LineStart* lineStart = &chunk->lines[chunk->lineCount++];
    lineStart->offset = chunk->count - 1;
    lineStart->line = line;
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(LineStart, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

size_t addConstant(Chunk* chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

int getLine(const Chunk* chunk, size_t instruction) {

    size_t start = 0;
    size_t end = chunk->lineCount - 1;

    for (;;) {

        size_t mid = (start + end) / 2;
        LineStart* line = &chunk->lines[mid];

        if (instruction < line->offset) {
            end = mid - 1;
        }
        else if (mid == chunk->lineCount - 1 || instruction < chunk->lines[mid + 1].offset) {
            return line->line;
        }
        else {
            start = mid + 1;
        }
    }

}