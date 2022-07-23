#include "repl.h"
#include "reader.h"
#include <iostream>
using std::cout, std::endl;

namespace mylisp {
//-------------------- GLOBALS --------------------
bool running = true;
MyLispType _Null = {};
MyLispType *Null = &_Null;

//-------------------- FUNCTIONS ------------------
MyLispType *READ(string input) {
  return Null;
}

string EVAL(MyLispType *input) {
  string ret;
//  delete input;
  return ret;
}

string PRINT(string input) {
  cout << input << endl;
  return "";
}

string rep(string input) { return PRINT(EVAL(READ(input))); }

} // namespace mylisp
