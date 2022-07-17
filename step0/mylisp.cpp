#include "mylisp.h"

namespace mylisp {
bool running = true;

string READ(string input) { return input; }

string EVAL(string input) {
  if (input.find(EOF) != string::npos)
    running = false;
  return input;
}

string PRINT(string input) { return input; }

string rep(string input) { return PRINT(EVAL(READ(input))); }
} // namespace mylisp
