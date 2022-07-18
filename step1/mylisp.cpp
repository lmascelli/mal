#pragma once
#include <string>
#include <string_view>
#include <vector>
using std::string, std::vector, std::string_view;

namespace mylisp {
extern bool running;

string READ(string input);
string EVAL(string input);
string PRINT(string input);
string rep(string input);

class Reader {
public:
  Reader(string &input);
  string_view next();
  string_view peek();

private:
  string &_input;
  string_view current;
  size_t m_index = 0, m_indext = 0;
};

Reader *read_str();
void read_form(Reader *reader);

vector<string> tokenize(string text);

} // namespace mylisp
