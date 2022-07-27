#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

#define ML_TYPEP(X) static_cast<MyLispType *>(X)
#define ML_SIGNALP(X) static_cast<MyLispSignal *>(X)
#define ML_SYMBOLP(X) static_cast<MyLispSymbol *>(X)
#define ML_FUNCTIONP(X) static_cast<MyLispFunction *>(X)
#define ML_NUMBERP(X) static_cast<MyLispNumber *>(X)
#define ML_STRINGP(X) static_cast<MyLispString *>(X)
#define ML_LISTP(X) static_cast<MyLispList *>(X)
#define ML_VECTORP(X) static_cast<MyLispVector *>(X)
#define ML_HASHMAPP(X) static_cast<MyLispHashMap *>(X)

namespace mylisp {
class MyLispType {
public:
  enum MyLispTYPE {
    NULL_TYPE,
    SIGNAL,
    SYMBOL,
    FUNCTION,
    NUMBER,
    STRING,
    LIST,
    VECTOR,
    HASHMAP,
  };
  MyLispTYPE type;
};

extern bool running;
extern MyLispType *Null;

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

class MyLispFunction : public MyLispType {
public:
  MyLispFunction(std::function<MyLispType *(MyLispType *)> fun);
  std::function<MyLispType *(MyLispType *)> _fun;
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
