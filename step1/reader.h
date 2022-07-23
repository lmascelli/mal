#pragma once
#include <string>
#include <string_view>
#include <vector>
using std::string, std::string_view, std::vector;

namespace mylisp{

class Reader {
public:
  Reader();
  string_view next();
  string_view peek();

private:
  friend void add_token(string_view& s);
  vector<string> tokens;
  int position = 0;
};

Reader read_str();
}
