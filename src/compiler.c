#include <stdlib.h>
#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "scanner.h"

void compile(const char* source) {
    initScanner(source);

    // Tokens on demand
    int line = -1;

    for (;;) {
        Token token = scanToken();
        if (token.line != line) {
            fprintf(stdout, "%4d ", token.line);
            line = token.line;
        }
        else {
            fprintf(stdout, "   | ");
        }
        fprintf(stdout, "%2d '%.*s'\n", token.type, token.length, token.start);

        if (token.type == TOKEN_EOF) break;
    }
}