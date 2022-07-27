#include "evaluer.h"
#include "repl.h"
#include <iostream>

using std::cout, std::endl;

namespace mylisp {

std::unordered_map<std::string, MyLispFunction *> repl_env;

void init_repl_env() {
  repl_env.insert(std::pair(
      "+", new MyLispFunction([](MyLispType *args) {
        if (args->type == MyLispType::LIST) {
          MyLispList *f_args = ML_LISTP(args);
          return ML_TYPEP(new MyLispNumber(
              static_cast<MyLispNumber *>(f_args->elements[1])->_number +
              static_cast<MyLispNumber *>(f_args->elements[2])->_number));
        } else {
          cout << "wrong arguments passed to + operator" << endl;
          return Null;
        }
      })));
  repl_env.insert(std::pair(
      "-", new MyLispFunction([](MyLispType *args) {
        if (args->type == MyLispType::LIST) {
          MyLispList *f_args = ML_LISTP(args);
          return ML_TYPEP(new MyLispNumber(
              static_cast<MyLispNumber *>(f_args->elements[1])->_number -
              static_cast<MyLispNumber *>(f_args->elements[2])->_number));
        } else {
          cout << "wrong arguments passed to + operator" << endl;
          return Null;
        }
      })));
  repl_env.insert(std::pair(
      "*", new MyLispFunction([](MyLispType *args) {
        if (args->type == MyLispType::LIST) {
          MyLispList *f_args = ML_LISTP(args);
          return ML_TYPEP(new MyLispNumber(
              static_cast<MyLispNumber *>(f_args->elements[1])->_number *
              static_cast<MyLispNumber *>(f_args->elements[2])->_number));
        } else {
          cout << "wrong arguments passed to + operator" << endl;
          return Null;
        }
      })));
  repl_env.insert(std::pair(
      "/", new MyLispFunction([](MyLispType *args) {
        if (args->type == MyLispType::LIST) {
          MyLispList *f_args = ML_LISTP(args);
          if (ML_NUMBERP(f_args->elements[2])->_number == 0) {
            cout << "division by 0" << endl;
            return Null;
          }
          return ML_TYPEP(new MyLispNumber(
              static_cast<MyLispNumber *>(f_args->elements[1])->_number /
              static_cast<MyLispNumber *>(f_args->elements[2])->_number));
        } else {
          cout << "wrong arguments passed to + operator" << endl;
          return Null;
        }
      })));
}

MyLispType *
eval_ast(MyLispType *ast,
         std::unordered_map<std::string, MyLispFunction *> repl_env) {
  switch (ast->type) {
  case MyLispType::SYMBOL: {
    if (repl_env.contains(ML_SYMBOLP(ast)->_keyword)) {
      return repl_env[ML_SYMBOLP(ast)->_keyword];
    } else {
      cout << "unknown symbol: " << ML_SYMBOLP(ast)->_symbol << endl;
      return Null;
    }
  }
  case MyLispType::LIST: {
    MyLispList *ret = new MyLispList, *list = ML_LISTP(ast);
    for (auto el : list->elements) {
      ret->elements.push_back(EVAL(el, repl_env));
    }
    return ret;
  }
  case MyLispType::VECTOR: {
    MyLispVector *ret = new MyLispVector, *vector = ML_VECTORP(ast);
    for (auto el: vector->elements) {
      ret->elements.push_back(EVAL(el, repl_env));
    }
    return ret;
  }
  case MyLispType::HASHMAP: {
    MyLispHashMap *ret = new MyLispHashMap, *hashmap = ML_HASHMAPP(ast);
    for (auto el: hashmap->map) {
      ret->map.insert(std::pair(el.first, EVAL(el.second, repl_env)));
    }
    return ret;
  }
  default:
    return ast;
  }
}
} // namespace mylisp
