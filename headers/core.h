#ifndef CORE_H
#define CORE_H

#include "alu.h"
#include "memory.h"


class Core {
private:
    i_ALU iALU;
    f_ALU fALU;

    void oper2alu();

public:
    Core();
    unsigned int instructionPtr;
    unsigned int r1;
    unsigned int r2;
    bool isWorking;
    char flags;
    Stack stack;

    void sum();
    void sumu();
    void mul();
    void mulu();
    void inc();
    void incu();
    void sumf();
    void mulf();
    void incf();
    void jmp();
    void hlt();
    void push();
    void pop();
    void cmp();
    void je();
    void jne();
};

#endif // CORE_H
