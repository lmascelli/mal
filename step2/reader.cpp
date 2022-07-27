#include "reader.h"
#include "repl.h"
#include <iostream>
#include <string>

using std::cout, std::endl;

namespace mylisp {

string_view Reader::next() { return string_view(tokens[position++]); }

string_view Reader::peek() { return string_view(tokens[position]); }

bool Reader::end() {
  return position >= (int)tokens.size() or tokens.size() == 0;
}

void Reader::reset() { position = -1; }

void add_token(Reader *r, string_view s) { r->tokens.push_back(string(s)); }

enum TOKEN_TYPE {
  INIT,
  CHAR,
  SPACE,
  BRACKET,
  STRING,
  STRING_CLOSED,
  STRING_SPECIAL_CHAR,
  EOL,
};

Reader *tokenize(string &input) {
  Reader *ret = new Reader;
  string_view view(input);
  unsigned int index = 0, offset = 0;
  TOKEN_TYPE last_token = INIT;

  while (index + offset < view.length()) {
    char ch = view.at(index + offset);
    if (last_token == STRING) {
      switch (ch) {
      case '\\':
        if (index + offset < view.length() - 2) {
          offset += 2;
        } else {
          cout << "ERROR: PARSING STRING OUT OF BOUNDS" << endl;
          abort();
        }
        break;
      case '"':
        add_token(ret, view.substr(index, offset + 1));
        index += offset + 1;
        offset = 0;
        last_token = STRING_CLOSED;
        break;
      default:
        offset++;
        break;
      }
    } else {
      switch (ch) {
      case ' ':
        if (last_token != SPACE and last_token != STRING_CLOSED and
            last_token != BRACKET) {
          add_token(ret, view.substr(index, offset));
          index += offset + 1;
          offset = 0;
        } else {
          index++;
          offset = 0;
        }
        last_token = SPACE;
        break;
      case '(':
      case ')':
      case '[':
      case ']':
      case '{':
      case '}':
        if (offset) {
          add_token(ret, view.substr(index, offset));
          index += offset;
          offset = 0;
        } else {
          add_token(ret, view.substr(index, 1));
          index++;
          offset = 0;
        }
        last_token = BRACKET;
        break;
      case '"': {
        index += offset;
        offset = 1;
        last_token = STRING;
      } break;
      case ';':
        return ret;
      default:
        offset++;
        last_token = CHAR;
      }
    }
#ifdef ML_DEBUG
    ret->reset();
    ret->debug();
    cout << view << endl;
    for (unsigned i = 0; i < view.length(); i++) {
      if (i == index)
        cout << "i";
      else
        cout << " ";
    }
    cout << endl;
    for (unsigned i = 0; i < view.length(); i++) {
      if (i == index + offset)
        cout << "*";
      else
        cout << " ";
    }
    cout << endl;
    std::cin.get();
#endif
  }
  if (index < view.length()) {
    add_token(ret, view.substr(index, offset));
  }
  if (last_token == STRING) {
    cout << "ERROR: STRING STILL OPEN" << endl;
    abort();
  }

  return ret;
}

MyLispType *read_form(Reader *r) {
  if (not r->end()) {
    r->next();
    if (r->peek() == "(")
      return read_list(r);
    else if (r->peek() == "[")
      return read_vector(r);
    else if (r->peek() == "{")
      return read_hashmap(r);
    else
      return read_atom(r);
  } else {
    return Null;
  }
}

MyLispType *read_list(Reader *r) {
#ifdef ML_DEBUG
  cout << "new list" << endl;
#endif
  MyLispList *ret = new MyLispList();
  bool correct = false;
  while (not correct) {
    MyLispType *el = read_form(r);
    if (el == Null)
      break;
    else if (el->type == MyLispType::SYMBOL and
             static_cast<MyLispSymbol *>(el)->_symbol ==
                 MyLispSymbol::LIST_BRACKET_CLOSE) {
      correct = true;
    } else {
#ifdef ML_DEBUG
      if (el->type == MyLispType::STRING) {
        cout << "list insert " << static_cast<MyLispString *>(el)->_str << endl;
      }
#endif
      ret->elements.push_back(el);
    }
  }
  if (correct)
    return ret;
  else
    return Null;
}

MyLispType *read_vector(Reader *r) {
  MyLispVector *ret = new MyLispVector;
  bool correct = false;
  while (not correct) {
    MyLispType *el = read_form(r);
    if (el == Null)
      break;
    else if (el->type == MyLispType::SYMBOL and
             static_cast<MyLispSymbol *>(el)->_symbol ==
                 MyLispSymbol::VECTOR_BRACKET_CLOSE) {
      correct = true;
    } else {
      ret->elements.push_back(el);
    }
  }
  if (correct)
    return ret;
  else
    return Null;
}

MyLispType *read_hashmap(Reader *r) {
  MyLispHashMap *ret = new MyLispHashMap;
  string key_s;
  MyLispType *value_p;
  bool correct = false;
  bool key = true;
  int i = 0;
  while (not correct) {
    MyLispType *el = read_form(r);
    std::cin.get();
    if (key) {
      key = false;
      if (el->type == MyLispType::STRING) {
        key_s = static_cast<MyLispString *>(el)->_str;
      } else if (el->type == MyLispType::SYMBOL and
                 static_cast<MyLispSymbol *>(el)->_symbol ==
                     MyLispSymbol::KEYWORD) {
        key_s = static_cast<MyLispSymbol *>(el)->_keyword;
      } else if (el->type == MyLispType::SYMBOL and
                 static_cast<MyLispSymbol *>(el)->_symbol ==
                     MyLispSymbol::HASHMAP_BRACKET_CLOSE) {
        key = true;
        correct = true;
        break;
      } else {
        cout << "Invalid hashmap key" << endl;
        break;
      }
      continue;
    } else {
      if (el->type == MyLispType::SYMBOL and
          static_cast<MyLispSymbol *>(el)->_symbol ==
              MyLispSymbol::HASHMAP_BRACKET_CLOSE)
        break;
      else {
        value_p = el;
      }
    }
    if (not key) {
      ret->map.insert({key_s, value_p});
      key = true;
    }
  }
  if (correct and key)
    return ret;
  else {
    cout << "Error parsing hashmap" << endl;
    return Null;
  }
}

MyLispType *read_atom(Reader *r) {
  string_view atom = r->peek();
  switch (atom.at(0)) {
  case '"':
    return new MyLispString(string(r->peek()));
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
    if (check_is_number(atom))
      return new MyLispNumber(std::stod(string(atom)));
  default:
    return switch_symbol(atom);
  }
  return new MyLispString(string(atom));
}

MyLispSymbol *switch_symbol(string_view &atom) {
  if (atom == "true")
    return new MyLispSymbol(MyLispSymbol::LOGICAL_TRUE);
  else if (atom == "false")
    return new MyLispSymbol(MyLispSymbol::LOGICAL_FALSE);
  else if (atom == "nil")
    return new MyLispSymbol(MyLispSymbol::NIL);
  else if (atom == ")")
    return new MyLispSymbol(MyLispSymbol::LIST_BRACKET_CLOSE);
  else if (atom == "]")
    return new MyLispSymbol(MyLispSymbol::VECTOR_BRACKET_CLOSE);
  else if (atom == "}")
    return new MyLispSymbol(MyLispSymbol::HASHMAP_BRACKET_CLOSE);
  else
    return new MyLispSymbol(MyLispSymbol::KEYWORD, string(atom));
}

bool check_is_number(string_view &atom) {
  bool ret = true;
  for (char c : atom) {
    if (not(isdigit(c) or c == '.' or c == ',')) {
      ret = false;
      break;
    }
  }
  return ret;
}

#ifdef ML_DEBUG
void Reader::debug() {
  cout << "n_tokens -> " << tokens.size() << endl
       << "current position -> " << position << endl;
  for (auto el : tokens)
    cout << el << " ";
  cout << endl;
}
#endif

} // namespace mylisp
