cmake_minimum_required(VERSION 3.27)
project(BetterTLHelp C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS "-static")
include_directories(include)

add_executable(BetterTLHelp src/main.c
        include/Native.h)
