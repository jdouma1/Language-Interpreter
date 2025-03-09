#include <iostream>
#ifndef TOKEN_H
#define TOKEN_H

class Token {
public:
    enum class TokenType {
        KEY,
        ID,
        OP,
        CONSTANT,
        ERR
    };
    Token() { this->tokenType = TokenType::ERR, this->token = ""; }
    Token(TokenType tokenType, std::string token) { this->tokenType = tokenType, this->token = token; }

    //Function which works with function directly below to return string representation of [tokenType] enum when printing
    friend std::ostream& operator<<(std::ostream& os, const TokenType& token) {
        switch (token) {
        case TokenType::KEY:
            return os << "KEY";
        case TokenType::ID:
            return os << "ID";
        case TokenType::OP:
            return os << "OP";
        case TokenType::CONSTANT:
            return os << "CONSTANT";
        case TokenType::ERR:
            return os << "ERR";
        default:
            return os << "UNKNOWN";
        }
    }
    //Function which overloads "<<" operator to print Token
    friend std::ostream& operator<<(std::ostream& os, const Token& obj) {
        os << obj.tokenType << " : " << obj.token;
        return os;
    }
private:
    TokenType tokenType;
    std::string token;
};
#endif