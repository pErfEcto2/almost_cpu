#ifndef MEMORY_H
#define MEMORY_H

#include <mutex>

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

#endif // MEMORY_H
