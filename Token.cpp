#include "Token.h"
#include <utility>
#include <sstream>
#include <iostream>

Token::Token(TokenType type, std::string description, int line) {
    // initialize all member variables
   value = std::move(description);
   lineNumber = line;
   typeOfToken = type;
}

string TokenTypeToString(TokenType tokenType) {
   switch (tokenType) {
      case TokenType::COLON:
         return "COLON";
      case TokenType::COLON_DASH:
         return "COLON_DASH";
      case TokenType::UNDEFINED:
         return "UNDEFINED";
      case TokenType::QUERIES:
         return "QUERIES";
      case TokenType::RULES:
         return "RULES";
      case TokenType::COMMA:
         return "COMMA";
      case TokenType::PERIOD:
         return "PERIOD";
      case TokenType::Q_MARK:
         return "Q_MARK";
      case TokenType::LEFT_PAREN:
         return "LEFT_PAREN";
      case TokenType::RIGHT_PAREN:
         return "RIGHT_PAREN";
      case TokenType::MULTIPLY:
         return "MULTIPLY";
      case TokenType::ADD:
         return "ADD";
      case TokenType::SCHEMES:
         return "SCHEMES";
      case TokenType::FACTS:
         return "FACTS";
      case TokenType::ID:
         return "ID";
      case TokenType::STRING:
         return "STRING";
      case TokenType::COMMENT:
         return "COMMENT";
      case TokenType::EOF_TYPE:
         return "EOF";
   }
   return "ERROR";
}

void Token::toString() {
   stringstream ss;
   ss << "(" + TokenTypeToString(typeOfToken) + "," + "\"" + value + "\",";
   ss <<  lineNumber;
   ss << ")";
   std::cout << ss.str() << endl;
   ss.clear();
}
