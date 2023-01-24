#pragma once

#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "rv32.h"

#define TEST_N 4

void test_ADDI(){
    struct cpu_t cpu;
    Reset(&cpu);

    Write4B(cpu.memory, 0, 0xfff00093); // addi x1,x0, -1
    Write4B(cpu.memory, 4, 0x00008113); // addi x2, x1, 0
    Write4B(cpu.memory, 8, 0x00110193); //addi x3, x2, 1

    Tick(&cpu);
    Tick(&cpu);
    Tick(&cpu);

    assert(cpu.reg[1] == 0xffffffff);
    assert(cpu.reg[2] == 0xffffffff);
    assert(cpu.reg[3] == 0);
}

void test_ADD(){
    struct cpu_t cpu;
    Reset(&cpu);

    Write4B(cpu.memory, 0, 0x00100093); // addi x1,x0, 1
    Write4B(cpu.memory, 4, 0x00200113); // addi x2, x0, 2
    Write4B(cpu.memory, 8, 0x002081b3); // add x3, x1, x2
    Write4B(cpu.memory, 12, 0x00308133); // add x2, x1, x3

    Tick(&cpu);
    Tick(&cpu);
    Tick(&cpu);

    assert(cpu.reg[1] == 1);
    assert(cpu.reg[2] == 2);
    assert(cpu.reg[3] == 3);

    Tick(&cpu);

    assert(cpu.reg[2] == 4);

}

void test_SETI(){
    struct cpu_t cpu;
    Reset(&cpu);

    Write4B(cpu.memory, 0, 0x00100093); // addi x1, x0, 1
    Write4B(cpu.memory, 4, 0xffe0a093); // slti x1, x1, -2
    Write4B(cpu.memory, 8, 0xffe00093); // addi x1, x0, -2
    Write4B(cpu.memory, 12, 0x0000a093); // slti x1, x1, 0;

    Write4B(cpu.memory, 16, 0x00200093); // addi x1, x0, 2
    Write4B(cpu.memory, 20, 0x0000b113); // sltiu x2, x1, 0
    Write4B(cpu.memory, 24, 0xfff0b113); // sltiu x2, x1, -1

    Tick(&cpu);
    Tick(&cpu);
    assert(cpu.reg[1] == 0);
    Tick(&cpu);
    Tick(&cpu);
    assert(cpu.reg[1] == 1);

    Tick(&cpu);
    Tick(&cpu);
    assert(cpu.reg[2] == 0);
    Tick(&cpu);
    assert(cpu.reg[2] == 1);

}

void test_LOGI(){
    struct cpu_t cpu;
    Reset(&cpu);

    Write4B(cpu.memory, 0, 0x00100093); // addi x1, x0, 1
    Write4B(cpu.memory, 4, 0xfff0c113); // xori x2, x1, -1
    Write4B(cpu.memory, 8, 0x0010c193); // xori x3, x1, 1
    Write4B(cpu.memory, 12, 0x00116113); // ori x2, x2, 1
    Write4B(cpu.memory,16, 0x00306193); // ori x3, x0, 3
    Write4B(cpu.memory,20, 0x0050e093); // ori x1, x1, 5

    Tick(&cpu);
    Tick(&cpu);
    Tick(&cpu);
    assert(cpu.reg[1] == 1);
    assert(cpu.reg[2] == 0xFFFFFFFE);
    assert(cpu.reg[3] == 0);

    Tick(&cpu);
    Tick(&cpu);
    Tick(&cpu);
    assert(cpu.reg[1] == 5);
    assert(cpu.reg[2] == -1);
    assert(cpu.reg[3] == 3);

}

void TestRunner(){
     typedef void(*testfptr)();
     testfptr tests[TEST_N] = {&test_ADDI, &test_ADD, &test_SETI, &test_LOGI};

     for(int i = 0; i < TEST_N; i++){
         printf("running test %d/%d... \n", i+1, TEST_N);
         tests[i]();
     }
}

