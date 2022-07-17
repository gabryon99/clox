#ifndef CLOX_CHUNK_H
#define CLOX_CHUNK_H

#include "common.h"
#include "value.h"

typedef enum {
    OP_CONSTANT,    // 2
    OP_RETURN       // 1
} OpCode;

typedef struct {
    int     line;
    size_t  offset;
} LineStart;

typedef struct {

    size_t      count;
    size_t      capacity;
    uint8_t*    code;

    size_t      lineCount;
    size_t      lineCapacity;
    LineStart*  lines;

    ValueArray  constants;
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
 * @param line In which line the associated instruction is
 */
void writeChunk(Chunk* chunk, uint8_t byte, int line);

/***
 * Deallocate the chunk and initialize to the beginning state.
 * @param chunk The chunk to deallocate.
 */
void freeChunk(Chunk* chunk);

/***
 * Add a new constant inside the constant pool.
 * @param chunk
 * @param value The constant to add inside the pool.
 * @return
 */
size_t addConstant(Chunk* chunk, Value value);

int getLine(const Chunk* chunk, size_t instruction);

#endif //CLOX_CHUNK_H
