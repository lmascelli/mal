#include <iostream>
#include "mylisp.h"
#include "linenoise.hpp"
using namespace std;

int main(int argc, char **argv){
  const string history_path = "history.txt";
  linenoise::LoadHistory(history_path.c_str());
  while (mylisp::running) {
    string cmd;
    if (linenoise::Readline("user> ", cmd)) break;
    cout << mylisp::rep(cmd) << endl;
    linenoise::AddHistory(cmd.c_str());
  }
  linenoise::SaveHistory(history_path.c_str());
  return 0;
}
