#include "tokenizer.h"

/*
 * ****************************** 
 * BEGINNING OF POSITION CLASS
 * ****************************** 
 */

 // Advances the current position in the text.
 // Checks whether the current character is a newline and increments line and column position accordingly
void Position::advance(char currChar) {
    index += 1;
    col += 1;

    if (currChar == '\n') {
        line += 1;
        col = 0;
    }
}

/*
 * ****************************** 
 * END OF POSITION CLASS
 * ****************************** 
 */

/*
 * ****************************** 
 * BEGINNING OF TOKENIZER CLASS
 * ****************************** 
 */

/*
 * Constructor which initializes the members:
 *     - "text" to input read in "Language Interpreter.cpp", 
 *     - "pos" to store current Position in input
 *     - "currChar" to store current character being read from input
 * and calls "advance()" to increment "pos" and "currStr" to first values in the "text"
 */ 
Tokenizer::Tokenizer(std::string text) {
    this->text = text;
    pos = Position(-1, 0, -1);
    currChar = '\0';
    advance();
}

// Increments the current position in the text and updates the "currChar" to current character being read
void Tokenizer::advance() {
    pos.advance(currChar);

    if (pos.getIndex() < text.size()) {
        currChar = text.at(pos.getIndex());
    }
    else {
        currChar = '\0';
    }
}

// Reads numeral input to decipher whether the token is an integer or float type and returns the appropriate token
Token Tokenizer::createNumber() {
    std::string numStr = "";
    int dotCount = 0;

    // While the input is not empty (reached the end), and is a digit or decimal point
    while (currChar != '\0' && (std::isdigit(currChar) || currChar == '.')) {
        if (currChar == '.') {
            // If one decimal point has already been used, the number is no longer a valid float representation, return an error token
            if (dotCount == 1) {
                numStr += currChar;
                return(Token(Token::TokenType::ERR, numStr));
            }
            dotCount += 1;
        }
        numStr += currChar;
        advance();
    }
    if (dotCount == 0) {
        return(Token(Token::TokenType::INT, numStr));
    }
    // Floating point number without digits following decimal point.
    // Ex) "0." or "1."
    if (numStr.back() == '.') {
        return(Token(Token::TokenType::ERR, numStr));
    }
    return(Token(Token::TokenType::FLOAT, numStr));
}

// Advances through the "text" to compare the input against the language grammar and syntax and create a list of tokens.
// Prints error message and returns if a syntax error is encountered, otherwise continues to create a list of tokens
void Tokenizer::createTokens() {
    while (currChar != '\0') {
        // Ignore whitespace
        if (std::isspace(currChar)) {
            advance();
        }
        else if (currChar == '+') {
            tokenList.push_back(Token(Token::TokenType::PLUS, "+"));
            advance();
        }
        else if (currChar == '-') {
            tokenList.push_back(Token(Token::TokenType::MINUS, "-"));
            advance();
        }
        else if (currChar == '*') {
            tokenList.push_back(Token(Token::TokenType::MUL, "*"));
            advance();
        }
        else if (currChar == '/') {
            tokenList.push_back(Token(Token::TokenType::DIV, "/"));
            advance();
        }
        else if (currChar == '(') {
            tokenList.push_back(Token(Token::TokenType::LPAREN, "("));
            advance();
        }
        else if (currChar == ')') {
            tokenList.push_back(Token(Token::TokenType::RPAREN, ")"));
            advance();
        }
        else if (std::isdigit(currChar)) {
            Position start = pos.getPositionCopy();
            tokenList.push_back(createNumber());

            // If an invalid number was provided, "tokenType" must be "ERR". Print an error message and return from reading input
            if (tokenList.back().getTokenTypeToString() == "ERR") {
                Position end = pos.getPositionCopy();
                Error e = Error(start, end, "Invalid Float", tokenList.back().getTokenValue());
                std::cout << e.toString() << std::endl;
                return;
            }
            advance();
        }
        // Character is not recognized in the language syntax. Print an error message and return from reading input
        else {
            Position start = pos.getPositionCopy();
            std::string str = "";
            str += currChar;
            advance();
            Position end = pos.getPositionCopy();
            IllegalCharError e = IllegalCharError(start, end, str);

            std::cout << e.toString() << std::endl;
            return;
        }
    }
    // After reaching the end of the input, print the list of tokens
    printTokens();
}

// Prints a formatted list of tokens
void Tokenizer::printTokens() {
    std::cout << "[";
    for (int i = 0; i < tokenList.size() - 1; ++i) {
        std::cout << tokenList.at(i).toString() << ", ";
    }
    std::cout << tokenList.at(tokenList.size() - 1).toString() << "]" << std::endl;
}
/*
 * ****************************** 
 * END OF TOKENIZER CLASS
 * ****************************** 
 */
