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
