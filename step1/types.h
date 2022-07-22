#pragma once
#include <vector>
#include <string>

namespace mylisp {
class MyLispType {
public:
  enum MyLispTYPE {
    SIGNAL,
    LIST,
    STRING,
  };
  MyLispTYPE type;
};

class MyLispList : public MyLispType {
public:
  MyLispList();
  std::vector<MyLispType *> elements;
};

class MyLispSignal : public MyLispType {
public:
  enum MyLispSIGNAL {
    _QUIT,
  };

  MyLispSignal(MyLispSIGNAL signal);

  MyLispSIGNAL _signal;
  static MyLispSignal *QUIT;
};

class MyLispString : public MyLispType {
public:
  std::string _str;
  MyLispString(std::string str);
};

} // namespace mylisp
