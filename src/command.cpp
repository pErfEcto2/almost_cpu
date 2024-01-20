#include "../headers/command.h"

Command::Command(Type t) {
    operA = "";
    operB = "";
    type = t;
}

Command::Command() {
    operA = "";
    operB = "";
}

std::string Command::desc() {
    switch (type) {
        case Type::mov:
            return std::string("mov instruction moves a value from an arg2 to an arg1");

        case Type::sum:
            return std::string("sum instruction adds an arg1(as int) and an arg2(as int) and moves a result to the arg1");

        case Type::sumu:
            return std::string("sumu instruction adds an arg1(as uint) and an arg2(as uint) and moves a result to the arg1");

        case Type::sumf:
            return std::string("sumf instruction adds an arg1(as float) and arg2(as float) and moves a result to the arg1");

        case Type::inc:
            return std::string("inc instruction increases arg1(as int) by one");

        case Type::incu:
            return std::string("incu instruction increases arg1(as uint) by one");

        case Type::incf:
            return std::string("incf instruction increases arg1(as float) by one");

        case Type::mul:
            return std::string("mul instruction multiplies arg1(as int) and arg2(as int) and moves a result to the arg1");

        case Type::mulf:
            return std::string("mulf instruction multiplies arg1(as uint) and arg2(as uint) and moves a result to the arg1");

        case Type::mulu:
            return std::string("mulu instruction multiplies arg1(as float) and arg2(as float) and moves a result to the arg1");

        case Type::jmp:
            return std::string("jmp instruction changes an instruction pointer of a core");

        case Type::strthread:
            return std::string("strthread instruction starts new thread by allowing new core to work");

        case Type::hlt:
            return std::string("hlt instruction stops an execution for a core");

        case Type::push:
            return std::string("push instruction pushes a value on the stack");

        case Type::pop:
            return std::string("pop instruction returns a value from the stack");

        case Type::cmp:
            return std::string("cmp instruction compares two operands and sets EQUALS(first operand == second operand) and LESS(first operand < second operand) flags(first operand cant be a number)");
        }

        return "";
}
