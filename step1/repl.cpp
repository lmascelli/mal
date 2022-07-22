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
  Reader r(input);
  MyLispType *root = r.read_token();
  return root;
}

string EVAL(MyLispType *input) {
  string ret;
  switch (input->type) {
  case MyLispType::SIGNAL: {
    MyLispSignal *signal = static_cast<MyLispSignal *>(input);
    if (input) {
      switch (signal->_signal) {
      case MyLispSignal::_QUIT:
        running = false;
      }
    }
  } break;
  case MyLispType::LIST: {
    return "List";
  } break;
  case MyLispType::STRING: {
    return static_cast<MyLispString *>(input)->_str;
  } break;
  default:
    ret = "Null";
  }
//  delete input;
  return ret;
}

string PRINT(string input) {
  cout << input << endl;
  return "";
}

string rep(string input) { return PRINT(EVAL(READ(input))); }

} // namespace mylisp
