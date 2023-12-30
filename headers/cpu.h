#ifndef CPU_H
#define CPU_H

#include "command.h"
#include <string>
#include "core.h"
#include "memory.h"
#include "vector.h"


class CPU {
private:
    Vector<Command> &commands;
    Memory &memory;
    Core *cores;

    unsigned int regA;
    unsigned int regB;
    int numOfCores;

    unsigned int oper2val(std::string oper, unsigned int i);
    void execCommand(Command command, unsigned int i);
    bool any_core_works();
    int avail_core();

public:
    CPU(Vector<Command> &c, Memory &m, int n);
    ~CPU();

    void run();
    std::string getStatus();
};

#endif // CPU_H
