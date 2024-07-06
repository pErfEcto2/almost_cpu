#include "../headers/lib.h"
#include <regex>
#include "../headers/memory.h"

Vector<std::string> str_split(std::string str, char pattern) {
    Vector<std::string> res;

    std::stringstream s(str);

    for (std::string line; std::getline(s, line, pattern);) {
       res.push_back(line);
    }

    return res;
}

std::string trim(const std::string &str) {
    std::string s(str);
    s.erase(0, s.find_first_not_of(" \n\t\r"));
    s.erase(s.find_last_not_of(" \t\r\n") + 1);
    return s;
}

bool is_num(std::string s) {
    std::regex pattern("-?\\d+(\\.\\d+)?");
    return std::regex_match(s, pattern);
}

unsigned int str2uint(std::string s) {
    unsigned int res;
    if (s.find(".") != std::string::npos) {
           float tmp = std::stof(s);
           res = *(unsigned int *)&tmp;
    }
    else res = std::stoul(s);
    return res;
}

float uint2float(unsigned int x) {
    return *(float *)&x;
}

int uint2int(unsigned int x) {
    return *(int *)&x;
}

std::string uint2hex(unsigned int n) {
    std::stringstream stream;
    stream << std::hex << n;
    return std::string(stream.str());
}

std::string char2bin_str(char s) {
    std::string res;
    for (int i = 0; i < 8; i++)
           res = std::to_string(((1 << i) & s) >> i) + res;

    return res;
}

std::string stack2str(unsigned int *values) {
    std::string res;
    for (int i = 0; i < STACK_SIZE; i++) res += uint2hex(values[i]) + " ";
    return res;
}

bool is_reg_or_mem(std::string s) {
    return s == "A" || s == "B" || s == "r1" || s == "r2" || s[0] == 'm';
}

std::string transform_memory(std::string oper, std::map<std::string, unsigned int> vars) {
    // transforms variables to memory addresses in complex memory expressions, like: m(a + b) -> m(m0 + m1)
    // "a" and "b" can be either a register, a variable, a memory address or a number
    if (oper.length() <= 2 || is_num(oper) || (oper[0] == 'm' && oper.find("(") == oper.npos)) return oper;

    std::string res{"m("};
    Vector<std::string> elems = str_split(trim(oper), '+'); // {"m( addr ", " offset )"}

    elems[0] = trim(elems[0].substr(elems[0].find("(") + 1)); // "addr"
    elems[1] = trim(elems[1].substr(0, elems[1].length() - 1)); // "offset"

    if (vars.find(elems[0]) != vars.end()) res += "m" + std::to_string(vars.at(elems[0])) + "+";
    else res += elems[0] + "+";

    if (vars.find(elems[1]) != vars.end()) res += "m" + std::to_string(vars.at(elems[1])) + ")";
    else res += elems[1] + ")";

    return res;
}















