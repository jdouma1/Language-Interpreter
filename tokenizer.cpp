#include "tokenizer.h"

Tokenizer::Tokenizer() {
    this->line = "";
    this->key = "\bif\b|\belse\s+if\b|\belse\b|\bfor\b|\bwhile\b|\bdo\s+while\b";
    this->id = "[a-zA-z_]+";
    this->op = "\+|\-|\*|\/|\(|\)";
    this->constant = "[0-9]+";
}

//Function matches syntax defined below to create Abstract Syntax Tree (AST)
//Keywords: [if], [else if], [else], [for], [while], [do while]
//Identifiers: [a-zA-z_]+
//Operators: [+], [-], [*], [/], [(], [)]
//Constants: [0-9]+

void Tokenizer::parseLine(std::string line) {
    //Create index [i] to traverse string input
    //Create string [tokenVal] to hold subset of list for tokenization
    int i = 0;
    std::string tokenVal = "";

    while (i < line.size()) {
        tokenVal.push_back(line.at(i));

        //String matches keyword exactly, push token
        if (std::regex_match(tokenVal, key)) {
            Token token = Token(Token::TokenType::KEY, tokenVal);
            Tokenizer::tokenList.push(token);
            tokenVal = "";
        }
        //String matches identifier, continue iteration while matching
        else if (std::regex_match(tokenVal, id)) {
            while (std::regex_match(tokenVal, id) && i < line.size()) {
                tokenVal.push_back(line.at(i));
                ++i;
            }
            //String matched but index out of bounds, push token
            if (i >= line.size()) {
                Token token = Token(Token::TokenType::ID, tokenVal);
                Tokenizer::tokenList.push(token);
                tokenVal = "";
                continue;
            }
            //String did not match
            //Reset iterator to last valid match instance
            //Remove last value of string that did not match token
            --i;
            tokenVal.pop_back();

            //Create token and push
            Token token = Token(Token::TokenType::ID, tokenVal);
            Tokenizer::tokenList.push(token);
            tokenVal = "";
        }
        //String matches operator, push token
        else if (std::regex_match(tokenVal, op)) {
            Token token = Token(Token::TokenType::OP, tokenVal);
            Tokenizer::tokenList.push(token);
            tokenVal = "";
        }
        //String matches constant, continue iteration while matching
        else if (std::regex_match(tokenVal, constant)) {
            while (std::regex_match(tokenVal, constant) && i < line.size()) {
                tokenVal.push_back(line.at(i));
                ++i;
            }
            //String matched but index out of bounds, push token
            if (i >= line.size()) {
                Token token = Token(Token::TokenType::ID, tokenVal);
                Tokenizer::tokenList.push(token);
                tokenVal = "";
                continue;
            }
            //String did not match
            //Reset iterator to last valid match instance
            //Remove last value of string that did not match token
            --i;
            tokenVal.pop_back();

            //Create token and push
            Token token = Token(Token::TokenType::CONSTANT, tokenVal);
            Tokenizer::tokenList.push(token);
            tokenVal = "";
        }
        ++i;
    }
    //Have reached end of input string and have stack of tokens
    std::cout << "PRINTING LIST OF TOKENS IN REVERSE\n" << std::endl;
    while (!Tokenizer::tokenList.empty()) {
        std::cout << Tokenizer::tokenList.top() << std::endl;
        Tokenizer::tokenList.pop();
    }
}