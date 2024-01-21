#ifndef MEMORY_H
#define MEMORY_H

#include <mutex>
#define STACK_SIZE 256

typedef struct memEl {
    unsigned int value;
    std::mutex mut;
} memEL;


class Memory {
private:
    memEl *memory;

public:
    unsigned int size;
    Memory(int n);
    ~Memory();
    memEl &operator[](unsigned int i);
};


class Stack {
public:
    unsigned int *values;
    unsigned char ptr;
    Stack();
    ~Stack();
    void push(unsigned int value);
    unsigned int pop();
};

#endif // MEMORY_H
