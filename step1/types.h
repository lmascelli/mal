#pragma once
#include <vector>
#include <string>

namespace mylisp {
class MyLispType {
public:
  enum MyLispTYPE {
    NULL_TYPE,
    SIGNAL,
    LIST,
    STRING,
    NUMBER,
    SYMBOL,
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

class MyLispNumber : public MyLispType {
public:
  MyLispNumber(double number);
  double _number;
};

class MyLispSymbol : public MyLispType {
  public:
    enum MyLispSYMBOLS {
      NIL,
      LOGICAL_TRUE,
      LOGICAL_FALSE,
      BRACKET_OPEN,
      BRACKET_CLOSE,
      KEYWORD,
    };

    MyLispSymbol(MyLispSYMBOLS symbol = KEYWORD, std::string keyword = "");

    MyLispSYMBOLS _symbol;
    std::string _keyword;
};
} // namespace mylisp
