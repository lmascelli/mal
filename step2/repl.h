#pragma once
#include <string>
#include "types.h"
#include "evaluer.h"

using std::string;

namespace mylisp {

void delete_ast(MyLispType*);

MyLispType *READ(string input);
MyLispType *EVAL(MyLispType *input,
            std::unordered_map<string, MyLispFunction *> repl_env);
string PRINT(MyLispType* input);
string rep(string input, std::unordered_map<string, MyLispFunction *> repl_env);

} // namespace mylisp
