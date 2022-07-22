#include "reader.h"
#include "mylisp.h"
#include <iostream>

namespace mylisp {

Reader::Reader(string &input) : _input(input) {}

string_view Reader::next() {
  string_view view(_input);
  bool found = false;

#define RETURN(X)                                                              \
  {                                                                            \
    if (index == t_index) {                                                    \
      current = view.substr(index, X);                                         \
      t_index++;                                                               \
      return current;                                                          \
    } else {                                                                   \
      current = view.substr(index, t_index - index);                           \
      index = t_index;                                                         \
      return current;                                                          \
    }                                                                          \
  }

  while (t_index < view.length() and not found) {
    char ch = view.at(t_index);
    char a;
    std::cin >> a;
    switch (ch) {
    case '~':
      if (t_index < (view.length() - 1) and view.at(t_index + 1) == '@')
        RETURN(1)
      else
        RETURN(0)
      break;
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
      RETURN(1)
      break;
    case ' ':
      {
        if (index == t_index) {
          t_index++;
        } else {
          current = view.substr(index, t_index - index);
          index = t_index;
          return current;
        }
      }
      break;
      /*
    case '"': {
      if (index == t_index) {
        current = view.substr(index, 0);
        t_index++;
        return current;
      } else {
        size_t cl = 0;
        do {
          if (view.at(t_index + cl) == '"' and
              view.at(t_index + cl - 1) != '\\') {
            current = view.substr(index, cl);
            index = t_index;
            return current;
          } else
            cl++;
        } while (t_index + cl < view.length());
      }
    } break;
    case '\\':
    case '.':
    case ';':
      RETURN(0)
      break;
    case '\r':
    case '\t':
    case '\n':
    case EOF:
    */
    default:
      t_index++;
    }
  }
  if (index == 0){
    index = -1;
    current = view;
    return view;
  } else {
    current = view.substr(index+1);
    index = -1;
    return current;
  }
}

string_view Reader::peek() { return current; }

bool Reader::end() { return index == -1; }

MyLispType* Reader::read_token(){
  string_view token = next();
  if (token.find(EOF) != std::string::npos){
    return MyLispSignal::QUIT;
  }
  else if (token == "("){
    return read_list();
  }
  else {
    return new MyLispString(std::string(token));
  }
  return Null;
}

MyLispList* Reader::read_list()
{
  MyLispList* list = new MyLispList;
  while (next() != ")"){
    list->elements.push_back(read_token());
  }
  return list;
}
}
