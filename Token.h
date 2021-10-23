#ifndef TOKEN_H
#define TOKEN_H
#include <string>
using namespace std;

enum class TokenType {
    UNDEFINED,
    COLON,
    COLON_DASH,
    QUERIES,
    RULES,
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    ID,
    STRING,
    COMMENT,
    EOF_TYPE,
};


class Token
{
private:
    // TODO: add member variables for information needed by Token

    int lineNumber;

    string typeOfTokenString;

public:
    Token(TokenType type, std::string description, int line);

    // TODO: add other needed methods
    void toString();
    TokenType typeOfToken;
    string value;
};

#endif // TOKEN_H

