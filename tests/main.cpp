#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#define STUPID_LSP
#include "../headers/alu.h"
#include "../headers/command.h"
#include "../headers/core.h"
#include "../headers/cpu.h"
#include "../headers/lib.h"
#include "../headers/memory.h"
#include "../headers/vector.h"

TEST(cpu2, any) {
  Vector<Command> cmds;
  Command cmd;

  cmd.type = Type::mov;
  cmd.operA = "m2";
  cmd.operB = "256";
  cmds.push_back(cmd);

  cmd.type = Type::mov;
  cmd.operA = "A";
  cmd.operB = "m(1+1)";
  cmds.push_back(cmd);

  Memory mem(32);
  CPU cpu(cmds, mem, 2);
  cpu.run();

  ASSERT_EQ(cpu.regA, 256);
}

TEST(transform_memory, any) {
  ASSERT_EQ(transform_memory("A", {}), "A");
  ASSERT_EQ(transform_memory("m10", {}), "m10");
  ASSERT_EQ(transform_memory("m100", {}), "m100");
  ASSERT_EQ(transform_memory("m1000", {}), "m1000");
  ASSERT_EQ(transform_memory("10", {}), "10");
  ASSERT_EQ(transform_memory("r1", {}), "r1");

  ASSERT_EQ(transform_memory("m(  m0  +   m1    )", {}), "m(m0+m1)");
  ASSERT_EQ(transform_memory("m(a + b)", {{"a", 1}, {"b", 2}}), "m(m1+m2)");
  ASSERT_EQ(transform_memory("m(  m0  +   b    )", {{"b", 2}}), "m(m0+m2)");
  ASSERT_EQ(transform_memory("m(  a  +   m0    )", {{"a", 1}}), "m(m1+m0)");
  ASSERT_EQ(transform_memory("m(  A  +   b    )", {{"b", 2}}), "m(A+m2)");
  ASSERT_EQ(transform_memory("m(  a  +   r1    )", {{"a", 1}}), "m(m1+r1)");
  ASSERT_EQ(transform_memory("m(  a  +   1    )", {{"a", 1}}), "m(m1+1)");

  ASSERT_EQ(transform_memory("m(  a  +   m0    )", {{"a", 1}}), "m(m1+m0)");
  ASSERT_EQ(transform_memory("m(  b  +   A    )", {{"b", 2}}), "m(m2+A)");
  ASSERT_EQ(transform_memory("m(  r1  +   a    )", {{"a", 1}}), "m(r1+m1)");
  ASSERT_EQ(transform_memory("m(  1  +   a    )", {{"a", 1}}), "m(1+m1)");
}

TEST(char2bin_str, any) {
  ASSERT_EQ(char2bin_str(0), "00000000");
  ASSERT_EQ(char2bin_str(1), "00000001");
  ASSERT_EQ(char2bin_str((char)255), "11111111");
}

TEST(uint2hex, any_tests) {
  ASSERT_EQ(uint2hex(3), "3");
  ASSERT_EQ(uint2hex(10), "a");
}

TEST(uint2, any_tests) {
  ASSERT_EQ(1, uint2int(1));
  ASSERT_LE(abs(1.1 - uint2float(1066192077)), 0.001);
}

TEST(is_num, any_tests) {
  ASSERT_TRUE(is_num("123"));
  ASSERT_TRUE(is_num("-123"));
  ASSERT_TRUE(is_num("1.2"));
  ASSERT_TRUE(is_num("-1.123"));
  ASSERT_FALSE(is_num("asdgf"));
}

TEST(str2uint, any_tests) {
  ASSERT_EQ(1, str2uint("1"));
  ASSERT_EQ(1066192077, str2uint("1.1"));
  ASSERT_EQ(4294967295, str2uint("-1"));

  EXPECT_THROW(str2uint("sdfg"), std::invalid_argument);
}

TEST(cpu, any_tests) {
  Vector<Command> cmds;
  Command cmd;

  cmd.type = Type::mov;
  cmd.operA = "A";
  cmd.operB = "5";
  cmds.push_back(cmd);

  cmd.type = Type::sum;
  cmd.operA = "A";
  cmd.operB = "5";
  cmds.push_back(cmd);

  cmd.type = Type::sumu;
  cmd.operA = "A";
  cmd.operB = "5";
  cmds.push_back(cmd);

  cmd.type = Type::sumf;
  cmd.operA = "A";
  cmd.operB = "5";
  cmds.push_back(cmd);

  cmd.type = Type::push;
  cmd.operA = "A";
  cmds.push_back(cmd);

  cmd.type = Type::pop;
  cmd.operA = "A";
  cmds.push_back(cmd);

  cmd.type = Type::mul;
  cmd.operA = "A";
  cmd.operB = "5";
  cmds.push_back(cmd);

  cmd.type = Type::mulf;
  cmd.operA = "m0";
  cmd.operB = "m0";
  cmds.push_back(cmd);

  cmd.type = Type::mulu;
  cmd.operA = "A";
  cmd.operB = "5";
  cmds.push_back(cmd);

  cmd.type = Type::mulf;
  cmd.operA = "m1";
  cmd.operB = "5";
  cmds.push_back(cmd);

  cmd.type = Type::mov;
  cmd.operA = "r1";
  cmd.operB = "1";
  cmds.push_back(cmd);

  cmd.type = Type::cmp;
  cmd.operA = "m1";
  cmd.operB = "m1";
  cmds.push_back(cmd);

  cmd.type = Type::mov;
  cmd.operA = "r2";
  cmd.operB = "1";
  cmds.push_back(cmd);

  cmd.type = Type::mov;
  cmd.operA = "B";
  cmd.operB = "1";
  cmds.push_back(cmd);

  cmd.type = Type::mov;
  cmd.operA = "m0";
  cmd.operB = "1";
  cmds.push_back(cmd);

  cmd.type = Type::sum;
  cmd.operA = "r1";
  cmd.operB = "1";
  cmds.push_back(cmd);

  cmd.type = Type::sum;
  cmd.operA = "r2";
  cmd.operB = "1";
  cmds.push_back(cmd);

  cmd.type = Type::sum;
  cmd.operA = "B";
  cmd.operB = "1";
  cmds.push_back(cmd);

  cmd.type = Type::sum;
  cmd.operA = "m0";
  cmd.operB = "m0";
  cmds.push_back(cmd);

  cmd.type = Type::inc;
  cmd.operA = "B";
  cmd.operB = "5";
  cmds.push_back(cmd);

  cmd.type = Type::incu;
  cmd.operA = "r2";
  cmd.operB = "5";
  cmds.push_back(cmd);

  cmd.type = Type::incu;
  cmd.operA = "r1";
  cmd.operB = "5";
  cmds.push_back(cmd);

  cmd.type = Type::sumf;
  cmd.operA = "r1";
  cmd.operB = "1";
  cmds.push_back(cmd);

  cmd.type = Type::sumf;
  cmd.operA = "r2";
  cmd.operB = "1";
  cmds.push_back(cmd);

  cmd.type = Type::sumf;
  cmd.operA = "B";
  cmd.operB = "1";
  cmds.push_back(cmd);

  cmd.type = Type::mulf;
  cmd.operA = "B";
  cmd.operB = "A";
  cmds.push_back(cmd);

  cmd.type = Type::mulf;
  cmd.operA = "r1";
  cmd.operB = "r2";
  cmds.push_back(cmd);

  cmd.type = Type::mulf;
  cmd.operA = "r2";
  cmd.operB = "r1";
  cmds.push_back(cmd);

  cmd.type = Type::sumf;
  cmd.operA = "m0";
  cmd.operB = "m0";
  cmds.push_back(cmd);

  cmd.type = Type::incf;
  cmd.operA = "r1";
  cmds.push_back(cmd);

  cmd.type = Type::incf;
  cmd.operA = "r2";
  cmds.push_back(cmd);

  cmd.type = Type::incf;
  cmd.operA = "B";
  cmds.push_back(cmd);

  cmd.type = Type::incf;
  cmd.operA = "m0";
  cmds.push_back(cmd);

  cmd.type = Type::incf;
  cmd.operA = "A";
  cmds.push_back(cmd);

  cmd.type = Type::jmp;
  cmd.operA = std::to_string(cmds.size() + 1);
  cmds.push_back(cmd);

  cmd.type = Type::je;
  cmd.operA = std::to_string(cmds.size() + 1);
  cmds.push_back(cmd);

  cmd.type = Type::jne;
  cmd.operA = std::to_string(cmds.size() + 1);
  cmds.push_back(cmd);
  cmds.push_back(Command(Type::hlt));

  Memory mem(32);

  try {
    CPU cpu(cmds, mem, -1);
  } catch (std::invalid_argument &e) {
    EXPECT_STREQ(e.what(), "invalid number of cores");
  }

  CPU cpu(cmds, mem, 2);
  cpu.run();
}

TEST(memory, any_tests) {
  Memory mem(10);
  mem[0].value = 5;

  ASSERT_EQ(mem[0].value, 5);

  EXPECT_THROW(mem[30], std::invalid_argument);
}

TEST(trim, any_tests) { ASSERT_EQ("test", trim("  test  ")); }

TEST(split, any_tests) {
  Vector<std::string> t = str_split(std::string("test\n\n\ntest\n\n\n"), '\n');

  for (int i{0}; i < t.size(); i++) {
    if (t[i].size() > 1)
      ASSERT_TRUE(t[i] == "test");
  }
}

TEST(vector, any_tests) {
  Vector<int> v;

  ASSERT_EQ(v.size(), 0);
  v.push_back(3);

  ASSERT_EQ(v.size(), 1);
  ASSERT_EQ(v[0], 3);

  try {
    v[-1];
  } catch (std::exception &e) {
    EXPECT_STREQ(e.what(), "index out of range");
  }

  try {
    v[10];
  } catch (std::exception &e) {
    EXPECT_STREQ(e.what(), "index out of range");
  }

  v.clear();
  ASSERT_EQ(v.size(), 0);

  for (int i{0}; i < 5; i++)
    v.push_back(i);

  for (auto &i : v) {
    ASSERT_EQ(i, v[i]);
  }

  for (auto &i : v.find(3)) {
    ASSERT_EQ(i, v[i]);
  }

  v.clear();

  for (int i{0}; i < 40; i++) {
    v.push_back(i);
  }
}

TEST(core, tests) {
  Core c;
  c.r1 = 2;
  c.r2 = 3;
  c.isWorking = true;
  c.instructionPtr = 0;

  c.sum();
  ASSERT_EQ(c.r1, 5);
  c.r1 = 2;

  c.sumu();
  ASSERT_EQ(c.r1, 5);
  c.r1 = 2;

  c.mul();
  ASSERT_EQ(c.r1, 6);
  c.r1 = 2;

  c.mulu();
  ASSERT_EQ(c.r1, 6);
  c.r1 = 2;

  c.inc();
  ASSERT_EQ(c.r1, 3);
  c.r1 = 2;

  c.incu();
  ASSERT_EQ(c.r1, 3);
  float two = 2;
  float three = 3;
  c.r1 = *(unsigned int *)&two;
  c.r2 = *(unsigned int *)&three;

  c.sumf();
  ASSERT_LE(abs(*(float *)&c.r1 - (float)5.0), 0.001);
  c.r1 = *(unsigned int *)&two;

  c.mulf();
  ASSERT_LE(abs(*(float *)&c.r1 - (float)6.0), 0.001);
  c.r1 = *(unsigned int *)&two;

  c.incf();
  ASSERT_LE(abs(*(float *)&c.r1 - 3), 0.001);

  c.jmp();
  ASSERT_EQ(c.instructionPtr, c.r1);

  c.hlt();
  ASSERT_FALSE(c.isWorking);

  c.r1 = 3;
  c.push();
  c.pop();
  ASSERT_EQ(c.r1, 3);
}

TEST(command, tests) {
  Command com(Type::inc);
  ASSERT_EQ(std::string("inc instruction increases arg1(as int) by one"),
            com.desc());

  Command c;
  c.type = Type::inc;
  ASSERT_EQ(std::string("inc instruction increases arg1(as int) by one"),
            com.desc());
}

TEST(i_ALU, tests) {
  i_ALU iALU;

  iALU.operA = 2;
  iALU.operB = 3;

  iALU.inc();
  ASSERT_EQ(3, iALU.res);

  iALU.incu();
  ASSERT_EQ(3, iALU.res);

  iALU.sum();
  ASSERT_EQ(5, iALU.res);

  iALU.sumu();
  ASSERT_EQ(5, iALU.res);

  iALU.mul();
  ASSERT_EQ(6, iALU.res);

  iALU.mulu();
  ASSERT_EQ(6, iALU.res);
}

TEST(f_ALU, tests) {
  f_ALU fALU;

  float a = 1.2, b = 2.0;
  fALU.operA = *(unsigned int *)&a;
  fALU.operB = *(unsigned int *)&b;

  fALU.incf();
  ASSERT_LE(abs(2.2 - *(float *)&fALU.res), 0.001);

  fALU.sumf();
  ASSERT_LE(abs(3.2 - *(float *)&fALU.res), 0.001);

  fALU.mulf();
  ASSERT_LE(abs(2.4 - *(float *)&fALU.res), 0.001);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
