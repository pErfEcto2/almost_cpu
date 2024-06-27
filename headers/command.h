#ifndef COMMAND_H
#define COMMAND_H

#include <string>

enum Type {
    mov,
    sum,
    sumu,
    sumf,
    inc,
    incu,
    incf,
    mul,
    mulu,
    mulf,
    jmp,
    strthread,
    push,
    pop,
    cmp,
    je,
    jne,
    slp,
    hlt
};

class Command {
    public:
        Command(Type t);
        Command();
        std::string operA;
        std::string operB;
        Type type;

        std::string desc();
};

#endif // COMMAND_H
