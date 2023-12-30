#include "../headers/cpu.h"
#include <stdexcept>
#include "../headers/lib.h"
#include <thread>
#include <mutex>


CPU::CPU(Vector<Command> &c, Memory &m, int n) : commands(c), memory(m) {
  if (n <= 0)
    throw std::invalid_argument("invalid number of cores");

  numOfCores = n;
  cores = new Core[n];

  regA = 0;
  regB = 0;

  cores[0].isWorking = true;
}

CPU::~CPU() {
  delete[] cores;
}

unsigned int CPU::oper2val(std::string oper, unsigned int i) {
  if (oper == "r1")
    return cores[i].r1;
  else if (oper == "r2")
    return cores[i].r2;
  else if (oper == "A")
    return regA;
  else if (oper == "B")
    return regB;
  else if (oper[0] == 'm') {
    memory[std::stoi(oper.substr(1))].mut.lock();
    return memory[std::stoi(oper.substr(1))].value;
  }
  return str2uint(oper);
}

void CPU::execCommand(Command command, unsigned int i) {
  unsigned int val;
  switch (command.type) {
  case Type::hlt:
    cores[i].isWorking = false;
    break;

  case Type::mov:
    val = oper2val(command.operB, i);

    if (command.operA == "r1")
      cores[i].r1 = val;
    else if (command.operA == "r2")
      cores[i].r2 = val;
    else if (command.operA == "A")
      regA = val;
    else if (command.operA == "B")
      regB = val;
    else {
      memory[std::stoi(command.operB.substr(1))].mut.unlock();

      memory[std::stoi(command.operA.substr(1))].mut.lock();
      memory[std::stoi(command.operA.substr(1))].value = val;
      memory[std::stoi(command.operA.substr(1))].mut.unlock();
    }

    break;

  case Type::sum:
  case Type::sumu:
  case Type::sumf:
    cores[i].r1 = oper2val(command.operA, i);
    if (command.operA == command.operB && command.operA[0] == 'm') {
        memory[std::stoi(command.operA.substr(1))].mut.unlock();
    }
    cores[i].r2 = oper2val(command.operB, i);

    switch (command.type) {
    case Type::sum:
      cores[i].sum();
    break;

    case Type::sumu:
      cores[i].sumu();
      break;

    case Type::sumf:
      cores[i].sumf();
      break;
    }

    if (command.operA == "r1")
      cores[i].r1 = cores[i].r1;
    else if (command.operA == "r2")
      cores[i].r2 = cores[i].r1;
    else if (command.operA == "A")
      regA = cores[i].r1;
    else if (command.operA == "B")
      regB = cores[i].r1;
    else {
      memory[std::stoi(command.operA.substr(1))].value = cores[i].r1;
      memory[std::stoi(command.operA.substr(1))].mut.unlock();
    }

    if (command.operB[0] == 'm') {
      memory[std::stoi(command.operB.substr(1))].mut.unlock();
    }

    break;

  case Type::inc:
  case Type::incu:
  case Type::incf:
    cores[i].r1 = oper2val(command.operA, i);

    switch (command.type) {
    case Type::inc:
      cores[i].inc();
      break;

    case Type::incu:
      cores[i].incu();
      break;

    case Type::incf:
      cores[i].incf();
      break;
    }

    if (command.operA == "r1")
      cores[i].r1 = cores[i].r1;
    else if (command.operA == "r2")
      cores[i].r2 = cores[i].r1;
    else if (command.operA == "A")
      regA = cores[i].r1;
    else if (command.operA == "B")
      regB = cores[i].r1;
    else {
      memory[std::stoi(command.operA.substr(1))].value = cores[i].r1;
      memory[std::stoi(command.operA.substr(1))].mut.unlock();
    }
    break;

  case Type::mul:
  case Type::mulu:
  case Type::mulf:
    cores[i].r1 = oper2val(command.operA, i);
    if (command.operA == command.operB && command.operA[0] == 'm') {
        memory[std::stoi(command.operA.substr(1))].mut.unlock();
    }
    cores[i].r2 = oper2val(command.operB, i);

    switch (command.type) {
    case Type::mul:
      cores[i].mul();
      break;

    case Type::mulu:
      cores[i].mulu();
      break;

    case Type::mulf:
      cores[i].mulf();
      break;
    }

    if (command.operA == "r1")
      cores[i].r1 = cores[i].r1;
    else if (command.operA == "r2")
      cores[i].r2 = cores[i].r1;
    else if (command.operA == "A")
      regA = cores[i].r1;
    else if (command.operA == "B")
      regB = cores[i].r1;
    else {
      memory[std::stoi(command.operA.substr(1))].value = cores[i].r1;
      memory[std::stoi(command.operA.substr(1))].mut.unlock();
    }

    if (command.operB[0] == 'm') {
      memory[std::stoi(command.operB.substr(1))].mut.unlock();
    }

    break;

  case Type::jmp:
    cores[i].instructionPtr = std::stoi(command.operA) - 1;
    break;
  }
}

bool CPU::any_core_works() {
  bool res = false;
  for (int i{0}; i < numOfCores; i++) res = res || cores[i].isWorking;
  return res;
}

int CPU::avail_core() {
  int res = -1;

  for (int i{0}; i < numOfCores; i++) {
    if (!cores[i].isWorking) {
      res = i;
      break;
    }
  }
  return res;
}

void CPU::run() {
  std::thread threads[numOfCores];

  while (any_core_works()) {
    for (int i{0}; i < numOfCores; i++) {
        if (cores[i].isWorking) {
            threads[i] = std::thread([this, i](){
                while (cores[i].isWorking) {
                    if (cores[i].instructionPtr >= commands.size()) {
                        cores[i].isWorking = false;
                        return;
                    }

                    if (commands[cores[i].instructionPtr].type == Type::strthread) return;

                    execCommand(commands[cores[i].instructionPtr], i);
                    cores[i].instructionPtr++;
                }
            });
        }
    }

    for (int i{0}; i < numOfCores; i++)    {
        try {
            threads[i].join();
        } catch (std::system_error &e) {}
    }

    for (int i{0}; i < numOfCores; i++) {
        if (cores[i].isWorking && commands[cores[i].instructionPtr].type == Type::strthread) {
            unsigned int new_core_instr_ptr = std::stoi(commands[cores[i].instructionPtr].operA);
            int new_core_index = avail_core();

            if (new_core_index == -1) throw std::runtime_error("too many threads");

            cores[new_core_index].instructionPtr = new_core_instr_ptr;
            cores[new_core_index].isWorking = true;

            cores[i].instructionPtr++;
        }
    }
  }
}

std::string CPU::getStatus() {
  std::string res;
  res += "Value of the regA: " + std::to_string(regA) + "(" + std::to_string(uint2int(regA)) + ", " + std::to_string(uint2float(regA)) + ")";
  res += "\nValue of the regB: " + std::to_string(regB) + "(" + std::to_string(uint2int(regB)) + ", " + std::to_string(uint2float(regB)) + ")";
  res += "\n\nNumber of cores: " + std::to_string(numOfCores);

  for (int i{0}; i < numOfCores; i++) {
    res += "\nCORE #" + std::to_string(i);
    res += "\nValue of the r1: " + std::to_string(cores[i].r1) + "(" + std::to_string(uint2int(cores[i].r1)) + ", " + std::to_string(uint2float(cores[i].r1)) + ")";
    res += "\nValue of the r2: " + std::to_string(cores[i].r2) + "(" + std::to_string(uint2int(cores[i].r2)) + ", " + std::to_string(uint2float(cores[i].r2)) + ")";
    res += "\nInstruction pointer is " +
           std::to_string(cores[i].instructionPtr) + "\n";
  }

  return res;
}
