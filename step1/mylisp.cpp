#include "mylisp.h"

namespace mylisp {
bool running = true;

string READ(string input) {
  Reader r(input);
  return r.next().data();
}

string EVAL(string input) {
  if (input.find(EOF) != string::npos)
    running = false;
  return input;
}

string PRINT(string input) { return input; }

string rep(string input) { return PRINT(EVAL(READ(input))); }

Reader::Reader(string &input) : _input(input) {}

string_view Reader::next() {
  string_view view(_input);
  while (m_index < view.length()) {
    char ch = view.at(m_index);
    switch (ch) {
    case '~':
      if (view.at(m_index + 1) == '@')
        current = view.substr(m_index, 2);
        return current;
    case '[':
    case ']':
    case '{':
    case '}':
    case '(':
    case ')':
    case '\'':
    case '`':
    case '^':
    case '@':
      current = view.substr(m_index, 1);
      return current;
    case '"': {
      size_t cl = 1;
      do {
        if (view.at(m_index + cl) == '"' and view.at(m_index + cl - 1) != '\\')
          break;
        cl++;
      } while (m_index + cl < view.length());
      return view.substr(m_index, cl);
    }
    case '\\':
    case '.':
    case ';':
    case '\r':
    case '\t':
    case '\n':
    case EOF:
      current = view.substr(m_index, 1);
      return current;
    }
    m_index++;
  }
  current = view.substr(m_index);
  return current;
}

string_view Reader::peek(){
  return current;
}

} // namespace mylisp
