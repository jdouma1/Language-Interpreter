#include "token.h"
#include <regex>
#include <stack>
#ifndef TOKENIZER_H
#define TOKENIZER_H

class Tokenizer {
public:
    Tokenizer();
    static void parseLine(std::string line);
    static std::regex key;
    static std::regex id;
    static std::regex op;
    static std::regex constant;
private:
    std::string line;
    static std::stack<Token> tokenList;
};

#endif