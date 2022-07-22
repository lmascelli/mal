#pragma once
#include <string>
#include <string_view>
#include "types.h"
using std::string, std::string_view;

namespace mylisp{

class Reader {
public:
  Reader(string &input);
  string_view next();
  string_view peek();
  MyLispType* read_token();
  MyLispList* read_list();
  bool end();

private:
  string &_input;
  string_view current;
  size_t index = 0, t_index = 0;
};
}
