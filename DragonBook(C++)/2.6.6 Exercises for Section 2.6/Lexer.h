#pragma once
#include "Token.h"
#include "WordToken.h"
#include "Tag.h"
#include "Num.h"

#include <ctype.h>
#include <iostream>
#include <fstream>
#include <iterator>
#include <map>

class Lexer{

  private:
  char peek;
  std::map<const char*, WordToken> words;
  void reserve(WordToken t){
    words.insert(std::make_pair(t.lexeme, t));
  }

  public:
  unsigned line;
  Lexer() : line(1), peek(' ') {
    reserve(WordToken(Tag::TRUE, "true"));
    reserve(WordToken(Tag::FALSE, "false"));
  }
  Token scan(std::fstream& sourceCode) {
    for (;; sourceCode >> peek){
      if (peek == ' ' || peek == '\t'){
        continue;
      }
      else if (peek == '\n'){
        ++line;
      }
      else {
        break;
      }

      if (isdigit(peek)){
        int v = 0;
        do {
          v = 10 * v + (int)peek;
          sourceCode >> peek;
        } while (isdigit(peek));

        return Num(v);

      }

      if (isalpha(peek)){

        std::string buffer = "";
        do {

          buffer += peek;
          sourceCode >> peek;

        } while (isalpha(peek) || isdigit(peek));

      }

    }
  }

};
