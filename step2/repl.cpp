#include "repl.h"
#include "printer.h"
#include "reader.h"
#include <iostream>
using std::cout, std::endl;

namespace mylisp {
//-------------------- GLOBALS --------------------
bool running = true;

//-------------------- FUNCTIONS ------------------

void delete_ast(MyLispType* ast){}

MyLispType *READ(string input) {
  Reader *r = tokenize(input);
  r->reset();
  MyLispType *ast = read_form(r);
  return ast;
}

MyLispType *EVAL(MyLispType *input,
                 std::unordered_map<string, MyLispFunction *> repl_env) {
  MyLispType *evalued_input = eval_ast(input, repl_env);

  if (evalued_input->type == MyLispType::LIST) {
    if (ML_LISTP(evalued_input)->elements.empty())
      return evalued_input;
    else {
      if (ML_LISTP(evalued_input)->elements[0]->type == MyLispType::FUNCTION) {
        return ML_FUNCTIONP(ML_LISTP(evalued_input)->elements[0])
            ->_fun(evalued_input);
      } else {
        cout << "function unknown";
        return Null;
      }
    }
  } else {
    return evalued_input;
  }
}

string PRINT(MyLispType *input) {
  string ret = print_element(input) + '\n';

  delete_ast(input);

  return ret;
}

string rep(string input,
           std::unordered_map<string, MyLispFunction *> repl_env) {
  return PRINT(EVAL(READ(input), repl_env));
}

} // namespace mylisp
