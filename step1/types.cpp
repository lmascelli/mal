#include "types.h"

namespace mylisp {
MyLispSignal::MyLispSignal(MyLispSignal::MyLispSIGNAL signal) {
  type = SIGNAL;
  _signal = signal;
}
MyLispSignal *MyLispSignal::QUIT = new MyLispSignal(MyLispSignal::_QUIT);

MyLispList::MyLispList() { type = LIST; }

MyLispString::MyLispString(std::string str) {
  type = STRING;
  _str = str;
}
} // namespace mylisp
