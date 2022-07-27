#pragma once
#include "types.h"
#include <string>

using std::string;

namespace mylisp {

string print_element(MyLispType *element);
string print_symbol(MyLispSymbol *symbol);
string print_string(MyLispString *str);
string print_list(MyLispList *list);
string print_vector(MyLispVector *vector);
string print_hashmap(MyLispHashMap *hashmap);

} // namespace mylisp
