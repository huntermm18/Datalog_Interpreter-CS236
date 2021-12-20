#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"
#include "DatalogProgram.h"
#include "Parser.h"

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;
    int lineNumber = 0;
    int maxRead = 0;
    Automaton* maxAutomaton{};

    void CreateAutomata();


public:
    Lexer();
    ~Lexer();

    void Run(std::string& input);
    int GetTokensVectorSize();
    vector<Token*> TokensWithoutComments();

};

#endif // LEXER_H

