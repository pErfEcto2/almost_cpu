#ifndef ALU_H
#define ALU_H

#define ZERO      0b00000001 // zero
#define FZERO     0b00000010 // float zero
#define NEGATIVE  0b00000100 // negative
#define FNEGATIVE 0b00001000 // float negative
#define EQUALS    0b00010000 // first operand equals to second
#define LESS      0b00100000 // first operand is less than second
#define f7        0b01000000 // extra
#define f8        0b10000000 // extra

class ALU {
public:
  unsigned int operA;
  unsigned int operB;
  unsigned int res;
  char *flags;
};

class i_ALU : public ALU {
public:
  void sum();
  void sumu();
  void mul();
  void mulu();
  void inc();
  void incu();
  void cmp();
};

class f_ALU : public ALU {
public:
  void sumf();
  void mulf();
  void incf();
};

#endif // ALU_H
