#ifndef LIB_H
#define LIB_H

#include "vector.h"
#include <string>
#include <map>

Vector<std::string> str_split(std::string s, char pattern);

std::string trim(const std::string &s);

bool is_num(std::string s);

unsigned int str2uint(std::string s);

float uint2float(unsigned int x);

int uint2int(unsigned int x);

std::string uint2hex(unsigned int n);

std::string char2bin_str(char s);

std::string stack2str(unsigned int *values);

bool is_reg_or_mem(std::string s);

std::string transform_memory(std::string oper, std::map<std::string, unsigned int> vars);

#endif // LIB_H
