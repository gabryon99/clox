cmake_minimum_required(VERSION 3.23)
project(clox C)

set(CMAKE_C_STANDARD 17)

add_executable(clox src/main.c include/common.h include/chunk.h src/chunk.c include/loxmemory.h src/loxmemory.c include/debug.h src/debug.c include/value.h src/value.c include/vm.h src/vm.c include/compiler.h src/compiler.c include/scanner.h src/scanner.c include/object.h src/object.c)

include_directories(./include/)