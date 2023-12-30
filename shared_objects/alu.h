#ifndef ALU_H
#define ALU_H

class ALU {
public:
    unsigned int operA;
    unsigned int operB;
    unsigned int res;
};

class i_ALU : public ALU {
public:
    void sum();
    void sumu();
    void mul();
    void mulu();
    void inc();
    void incu();
};

class f_ALU : public ALU {
public:
    void sumf();
    void mulf();
    void incf();
};

#endif // ALU_H
