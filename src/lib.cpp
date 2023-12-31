#include "../headers/lib.h"
#include <iostream>
#include <regex>

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
