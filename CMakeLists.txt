cmake_minimum_required(VERSION 3.22)
project(rv32 C)

set(CMAKE_C_STANDARD 99)

add_executable(rv32 main.c rv32.h tests.h)
