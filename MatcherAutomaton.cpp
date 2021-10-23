

#include "MatcherAutomaton.h"
#include <utility>

MatcherAutomaton::MatcherAutomaton(std::string toMatch, TokenType tokenType) {
   this->toMatch = std::move(toMatch);
   type = tokenType;
}

int MatcherAutomaton::S0(const std::string& input) {
   bool isMatch = true;
   inputRead = 0;  // member variable inherited from Automaton class
   for (int i = 0; i < (int)toMatch.size() && isMatch; i++) {
      if (input[i] != toMatch[i]) {
         isMatch = false;
      }
   }
   if (isMatch) {
      inputRead = toMatch.size();
   }
   else {
      Serr();
   }
   return inputRead;
}