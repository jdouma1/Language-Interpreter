#include "tokenizer.h"

int main() {
    //std::cout << "Hello World!" << std::endl;
    //Token t = Token(Token::tokenType::OP, "+");
    //std::cout << "My token:\n" << t << std::endl;

    std::string line;
    std::cout << "Welcome! Press \'e\' to exit" << std::endl;
    while (true) {
        std::getline(std::cin, line);
        if (line == "e") {
            std::cout << "Goodbye" << std::endl;
            break;
        }
        else { Tokenizer::parseLine(line); }
    }

    return 0;
}
