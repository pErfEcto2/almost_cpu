#include "../headers/core.h"
#include <thread>

Core::Core() {
    instructionPtr = 0;
    isWorking = false;
    flags = 0;
    iALU.flags = &flags;
    fALU.flags = &flags;
}

void Core::oper2alu() {
    iALU.operA = *(unsigned int*)&r1;
    iALU.operB = *(unsigned int*)&r2;
    fALU.operA = *(unsigned int*)&r1;
    fALU.operB = *(unsigned int*)&r2;
}

void Core::sum() {
    oper2alu();
    iALU.sum();
    r1 = iALU.res;
}

void Core::sumu() {
    oper2alu();
    iALU.sumu();
    r1 = iALU.res;
}

void Core::sumf() {
    oper2alu();
    fALU.sumf();
    r1 = fALU.res;
}

void Core::mul() {
    oper2alu();
    iALU.mul();
    r1 = iALU.res;
}

void Core::mulf() {
    oper2alu();
    fALU.mulf();
    r1 = fALU.res;
}

void Core::mulu() {
    oper2alu();
    iALU.mulu();
    r1 = iALU.res;
}

void Core::slp() {
    std::this_thread::sleep_for(std::chrono::milliseconds(r1));
}

void Core::inc() {
    oper2alu();
    iALU.inc();
    r1 = iALU.res;
}

void Core::incu() {
    oper2alu();
    iALU.incu();
    r1 = iALU.res;
}

void Core::incf() {
    oper2alu();
    fALU.incf();
    r1 = fALU.res;
}

void Core::jmp() {
    instructionPtr = r1;
}

void Core::je() {
    if (flags & EQUALS)
        instructionPtr = r1;
}

void Core::jne() {
    if (!(flags & EQUALS))
        instructionPtr = r1;
}

void Core::hlt() {
    isWorking = false;
}

void Core::push() {
    stack.push(r1);
}

void Core::pop() {
    r1 = stack.pop();
}

void Core::cmp() {
    oper2alu();
    iALU.cmp();
}
