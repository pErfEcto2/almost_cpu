#include "../headers/alu.h"

// sorry for about u're going to see...

void i_ALU::sum() {
    int tmp = *(int*)&operA + *(int*)&(operB);
    res = *(unsigned int*)&tmp;
    *flags = (*flags & ~ZERO)     | ((tmp == 0) ? ZERO     : 0);
    *flags = (*flags & ~NEGATIVE) | ((tmp <  0) ? NEGATIVE : 0);
}

void i_ALU::sumu() {
    res = operA + operB;
    *flags = (*flags & ~ZERO)     | ((res == 0) ? ZERO : 0);
    *flags &= ~NEGATIVE;
}

void i_ALU::mul() {
    int tmp = *(int*)&operA * *(int*)&(operB);
    res = *(unsigned int*)&tmp;
    *flags = (*flags & ~ZERO)     | ((tmp == 0) ? ZERO     : 0);
    *flags = (*flags & ~NEGATIVE) | ((tmp <  0) ? NEGATIVE : 0);
}

void i_ALU::mulu() {
    res = operA * operB;
    *flags = (*flags & ~ZERO)     | ((res == 0) ? ZERO : 0);
    *flags &= ~NEGATIVE;
}

void i_ALU::inc() {
    int tmp = *(int*)&operA + 1;
    res = *(unsigned int*)&tmp;
    *flags = (*flags & ~ZERO)     | ((tmp == 0) ? ZERO     : 0);
    *flags = (*flags & ~NEGATIVE) | ((tmp <  0) ? NEGATIVE : 0);
}

void i_ALU::incu() {
    res = operA + (unsigned int)1;
    *flags = (*flags & ~ZERO)     | ((res == 0) ? ZERO : 0);
    *flags &= ~NEGATIVE;
}

void i_ALU::cmp() {
    *flags = (*flags & ~EQUALS) | ((operA == operB) ? EQUALS : 0);
    *flags = (*flags & ~LESS)   | ((operA <  operB) ? LESS   : 0);
}

void f_ALU::sumf() {
    float tmp = *(float*)&operA + *(float*)&operB;
    res = *(unsigned int*)&tmp;
    *flags = (*flags & ~FZERO)     | ((tmp == 0) ? FZERO     : 0);
    *flags = (*flags & ~FNEGATIVE) | ((tmp <  0) ? FNEGATIVE : 0);
}

void f_ALU::mulf() {
    float tmp = *(float*)&operA * *(float*)&operB;
    res = *(unsigned int*)&tmp;
    *flags = (*flags & ~FZERO)     | ((tmp == 0) ? FZERO     : 0);
    *flags = (*flags & ~FNEGATIVE) | ((tmp <  0) ? FNEGATIVE : 0);
}

void f_ALU::incf() {
    float tmp = *(float*)&operA + 1;
    res = *(unsigned int*)&tmp;
    *flags = (*flags & ~FZERO)     | ((tmp == 0) ? FZERO     : 0);
    *flags = (*flags & ~FNEGATIVE) | ((tmp <  0) ? FNEGATIVE : 0);
}
