#include "../headers/alu.h"

void i_ALU::sum() {
    int tmp = *(int*)&operA + *(int*)&(operB);
    res = *(unsigned int*)&tmp;
}

void i_ALU::sumu() { res = operA + operB; }

void i_ALU::mul() {
    int tmp = *(int*)&operA * *(int*)&(operB);
    res = *(unsigned int*)&tmp;
}

void i_ALU::mulu() { res = operA * operB; }

void i_ALU::inc() {
    int tmp = *(int*)&operA + 1;
    res = *(unsigned int*)&tmp;
}

void i_ALU::incu() { res = operA + (unsigned int)1; }

void f_ALU::sumf() {
    float tmp = *(float*)&operA + *(float*)&operB;
    res = *(unsigned int*)&tmp;
}

void f_ALU::mulf() {
    float tmp = *(float*)&operA * *(float*)&operB;
    res = *(unsigned int*)&tmp;
}

void f_ALU::incf() {
    float tmp = *(float*)&operA + 1;
    res = *(unsigned int*)&tmp;
}

