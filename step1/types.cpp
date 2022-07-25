#include "types.h"
#include <iostream>

namespace mylisp {
MyLispType _Null = {};
MyLispType *Null = &_Null;

MyLispSignal::MyLispSignal(MyLispSignal::MyLispSIGNAL signal) {
  type = SIGNAL;
  _signal = signal;
}
MyLispSignal *MyLispSignal::QUIT = new MyLispSignal(MyLispSignal::_QUIT);

MyLispList::MyLispList() { type = LIST; }

MyLispString::MyLispString(std::string str) {
  type = STRING;
  bool check_next = false;
  unsigned int i = 0;
  for (char a : str) {
    if (i == 0 or i == str.length() - 1){
      i++;
      continue;
    }
    else {
      if (check_next) {
        switch (a) {
        case '"':
          _str += '"';
          break;
        case 'n':
          _str += '\n';
          break;
        case '\\':
          _str += '\\';
          break;
        }
        check_next = false;
      } else {
        if (a == '\\')
          check_next = true;
        else {
          _str += a;
        }
      }
    }
    i++;
  }
}

MyLispNumber::MyLispNumber(double number) {
  type = MyLispType::NUMBER;
  _number = number;
}

MyLispSymbol::MyLispSymbol(MyLispSYMBOLS symbol, std::string keyword) {
  type = MyLispType::SYMBOL;
  _symbol = symbol;
  _keyword = keyword;
}
} // namespace mylisp
