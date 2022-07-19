#ifndef CLOX_CHUNK_H
#define CLOX_CHUNK_H

#include "common.h"
#include "value.h"

typedef enum {
    OP_RETURN,          // 0
    OP_CONSTANT,        // 1
    OP_CONSTANT_LONG,   // 2
    OP_NEGATE,          // 3
    OP_ADD,             // 4
    OP_SUBTRACT,        // 5
    OP_MULTIPLY,        // 6
    OP_DIVIDE,          // 7,
    OP_NIL,
    OP_TRUE,
    OP_FALSE,
    OP_NOT,
    OP_EQUAL,           // (a != b) = !(a == b)
    OP_GREATER,         // (a >= b) = !(a <  b)
    OP_LESS,            // (a <= b) = !(a >  b)
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

void writeConstant(Chunk* chunk, Value value, int line);

#endif //CLOX_CHUNK_H
