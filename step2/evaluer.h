#pragma once
#include <unordered_map>
#include <functional>
#include "types.h"

namespace mylisp {
extern std::unordered_map<std::string, MyLispFunction *> repl_env;

void init_repl_env();

MyLispType *
eval_ast(MyLispType *ast,
         std::unordered_map<std::string, MyLispFunction *> repl_env);
} // namespace mylisp
