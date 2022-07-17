#pragma once
#include <string>
#include <string_view>
#include <vector>
using std::string, std::vector;

namespace mylisp {
extern bool running;

string READ(string input);
string EVAL(string input);
string PRINT(string input);
string rep(string input);

class Reader {
  public:
    string next();
    string peek();
};

Reader* read_str();
void read_form(Reader* reader);

class Tokenizer {
  public:
    Tokenizer(string &input);

  private:
    string &m_imput;

};

vector<string> tokenize(string text);

} // namespace mylisp
