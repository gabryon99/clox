#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm.h"
#include "debug.h"

static char* readFile(const char* path) {

    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Could not open file '%s'.\n", path);
        exit(74);
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);

    rewind(file);

    char* buffer = (char*) malloc((fileSize + 1) * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Not enough memory to read file '%s'.\n", path);
        exit(74);
    }

    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    if (bytesRead < fileSize) {
        fprintf(stderr, "Could not read file '%s'.\n", path);
        exit(74);
    }

    buffer[bytesRead] = '\0';

    fclose(file);

    return buffer;
}

static void repl() {
#define LINE_BUFFER 1024

    char line[LINE_BUFFER];

    fprintf(stdout, "clox v0.1\n");
    for (; ;) {
        fprintf(stdout, "> ");
        if (!fgets(line, sizeof(line), stdin)) {
            fprintf(stdout, "\n");
            break;
        }
        interpret(line);
    }

#undef LINE_BUFFER
}

static void runFile(const char* filepath) {

    char* source = readFile(filepath);
    InterpretResult result = interpret(source);
    free(source);

    if (result == INTERPRET_COMPILE_ERROR) exit(65);
    if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

int main(int argc, const char* argv[]) {

    initVM();

    if (argc == 1) {
        repl();
    }
    else if (argc == 2) {
        runFile(argv[1]);
    }
    else {
        fprintf(stderr, "Usage: clox [path]\n");
        return 64;
    }

    freeVM();

    return 0;
}
