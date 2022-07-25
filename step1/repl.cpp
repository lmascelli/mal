#include "repl.h"
#include "printer.h"
#include "reader.h"
#include <iostream>
using std::cout, std::endl;

namespace mylisp {
//-------------------- GLOBALS --------------------
bool running = true;

//-------------------- FUNCTIONS ------------------
MyLispType *READ(string input) {
  Reader *r = tokenize(input);
  r->reset();
  MyLispType* ast = read_form(r);
  return ast;
}

string EVAL(MyLispType *input) {
  string ret = "";
  ret = print_element(input);
  //  delete input;
  return ret;
}

string PRINT(string input) {
  cout << input << endl;
  return "";
}

string rep(string input) { return PRINT(EVAL(READ(input))); }

} // namespace mylisp
