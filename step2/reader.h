#pragma once

// #define ML_DEBUG

#include "types.h"
#include <string>
#include <string_view>
#include <vector>
using std::string, std::string_view, std::vector;

namespace mylisp {

class Reader {
public:
  string_view next();
  string_view peek();
  bool end();
  void reset();
#ifdef ML_DEBUG
  void debug();
#endif

private:
  friend void add_token(Reader *r, string_view s);
  vector<string> tokens;
  int position = -1;
};

Reader *tokenize(string &input);

MyLispType *read_form(Reader *r);
MyLispType *read_list(Reader *r);
MyLispType *read_vector(Reader *r);
MyLispType *read_hashmap(Reader *r);
MyLispType *read_atom(Reader *r);

MyLispSymbol *switch_symbol(string_view &atom);
bool check_is_number(string_view &atom);

} // namespace mylisp
