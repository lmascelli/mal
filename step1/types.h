#pragma once
#include <vector>
#include <string>
#include <unordered_map>

namespace mylisp {
class MyLispType {
public:
  enum MyLispTYPE {
    NULL_TYPE,
    SIGNAL,
    SYMBOL,
    NUMBER,
    STRING,
    LIST,
    VECTOR,
    HASHMAP,
  };
  MyLispTYPE type;
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

class MyLispSymbol : public MyLispType {
public:
  enum MyLispSYMBOLS {
    NIL,
    LOGICAL_TRUE,
    LOGICAL_FALSE,
    LIST_BRACKET_OPEN,
    LIST_BRACKET_CLOSE,
    VECTOR_BRACKET_OPEN,
    VECTOR_BRACKET_CLOSE,
    HASHMAP_BRACKET_OPEN,
    HASHMAP_BRACKET_CLOSE,
    KEYWORD,
  };

  MyLispSymbol(MyLispSYMBOLS symbol = KEYWORD, std::string keyword = "");

  MyLispSYMBOLS _symbol;
  std::string _keyword;
};

class MyLispNumber : public MyLispType {
public:
  MyLispNumber(double number);
  double _number;
};

class MyLispString : public MyLispType {
public:
  std::string _str;
  MyLispString(std::string str);
};

class MyLispList : public MyLispType {
public:
  MyLispList();
  std::vector<MyLispType *> elements;
};

class MyLispVector : public MyLispType {
public:
  MyLispVector();
  std::vector<MyLispType *> elements;
};

class MyLispHashMap : public MyLispType {
public:
  MyLispHashMap();
  std::unordered_map<std::string, MyLispType *> map;
};
} // namespace mylisp
