#ifndef CLOX_CHUNK_H
#define CLOX_CHUNK_H

#include "common.h"

typedef enum {
    OP_RETURN
} OpCode;

typedef struct {
    size_t count;
    size_t capacity;
    uint8_t* code;
} Chunk;

/***
 * Initialize a new Chunk of bytecode instructions.
 * @param chunk Chunk to initialize.
 */
void initChunk(Chunk* chunk);

/***
 * Write a byte inside a chunk.
 * @param chunk The chunk where the byte will be written.
 * @param byte The byte to write.
 */
void writeChunk(Chunk* chunk, uint8_t byte);

/***
 * Deallocate the chunk and initialize to the beginning state.
 * @param chunk The chunk to deallocate.
 */
void freeChunk(Chunk* chunk);

#endif //CLOX_CHUNK_H
