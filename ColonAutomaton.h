#ifndef COLONAUTOMATON_H
#define COLONAUTOMATON_H

#include "Automaton.h"

class ColonAutomaton : public Automaton
{
public:
    ColonAutomaton() : Automaton(TokenType::COLON) {}  // Call the base constructor

    int S0(const std::string& input);
};

#endif // COLONAUTOMATON_H

