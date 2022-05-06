#pragma once
#include "Token.h"
#include <cstring>
class WordToken : public Token {

    public:
    const char* lexeme;
    WordToken(int t, const char* s) : Token(t), lexeme(s) {}

};