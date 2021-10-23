
#ifndef PROJECT1_STARTER_CODE_MATCHERAUTOMATON_H
#define PROJECT1_STARTER_CODE_MATCHERAUTOMATON_H

#include "Automaton.h"
#include <string>


class MatcherAutomaton : public Automaton {
private:
    std::string toMatch;
public:

    MatcherAutomaton(std::string toMatch, TokenType tokenType);
    int S0(const std::string& input);
};


#endif //PROJECT1_STARTER_CODE_MATCHERAUTOMATON_H
