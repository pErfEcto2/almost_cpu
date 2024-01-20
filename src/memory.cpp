#include "../headers/memory.h"
#include <stdexcept>

Memory::Memory(int n) {
    size = n;
    memory = new memEL[size];
}

Memory::~Memory() { delete[] memory; }

memEL &Memory::operator[](unsigned int i) {
    if (i < 0 || i >= size) throw std::invalid_argument("invalid memory address");
    return memory[i];
}

Stack::Stack() {
    values = new unsigned int[STACK_SIZE];
    ptr = 0;
}

Stack::~Stack() {
    delete[] values;
}

void Stack::push(unsigned int value) {
    values[ptr] = value;
    ptr++;
}

unsigned int Stack::pop() {
    return values[--ptr];
}
