#pragma once
#include <string>
using std::string;

namespace mylisp {
extern bool running;

string READ(string input);
string EVAL(string input);
string PRINT(string input);
string rep(string input);
} // namespace mylisp
