#pragma once
#include <string>
#include "types.h"

using std::string;

namespace mylisp {
extern bool running;
extern MyLispType* Null;

MyLispType* READ(string input);
string EVAL(MyLispType* input);
string PRINT(string input);
string rep(string input);

} // namespace mylisp
