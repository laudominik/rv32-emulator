#pragma once

#include <stdint.h>
#include <assert.h>
#include "rv32.h"

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

