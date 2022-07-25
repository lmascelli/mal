#include "printer.h"
#include <iostream>

namespace mylisp {

string print_list(MyLispList *list) {
  string ret = "(";
  for (auto element : list->elements) {
    ret += print_element(element);
    ret += " ";
  }
  ret += ")";
  return ret;
}

string print_string(MyLispString *str) { return str->_str; }

string print_symbol(MyLispSymbol *symbol) {
  string ret = "";
  switch (symbol->_symbol) {
  case MyLispSymbol::KEYWORD:
    ret += '<' + symbol->_keyword + '>';
    break;
  case MyLispSymbol::LOGICAL_TRUE:
    ret += "<logical true>";
    break;
  case MyLispSymbol::LOGICAL_FALSE:
    ret += "<logical false>";
    break;
  case MyLispSymbol::NIL:
    ret += "<nil value>";
    break;
  default:
    ret += "ERROR print_symbol";
  }
  return ret;
}

string print_number(MyLispNumber *num) {
  return "*" + std::to_string(num->_number) + "*";
}

string print_element(MyLispType *element) {
  string ret = "";
  switch (element->type) {
  case MyLispType::NULL_TYPE:
    std::cout << "#Null" << std::endl;
    break;
  case MyLispType::LIST:
    ret += print_list(static_cast<MyLispList *>(element));
    break;
  case MyLispType::STRING:
    ret += print_string(static_cast<MyLispString *>(element));
    break;
  case MyLispNumber::NUMBER:
    ret += print_number(static_cast<MyLispNumber *>(element));
    break;
  case MyLispType::SYMBOL:
    ret += print_symbol(static_cast<MyLispSymbol *>(element));
    break;
  default:
    ret += "ERROR print_element";
  }
  return ret;
}
} // namespace mylisp
