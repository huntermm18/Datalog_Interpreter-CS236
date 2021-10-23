
#include "IdentifierAutomaton.h"

int IdentifierAutomaton::S0(const std::string& input) {
   if (isalpha(input[index])) {
      inputRead++;
      index++;
      S1(input);
   }
   else {
      Serr();
   }

   // check for reserved words
   if (input.substr(0,6) == "Facts ") {Serr();}
   if (input.substr(0,8) == "Queries ") {Serr();}
   if (input.substr(0,8) == "Schemes ") {Serr();}
   if (input.substr(0,6) == "Rules ") {Serr();}

   return inputRead;
}

void IdentifierAutomaton::S1(const std::string& input) {
   while (isalnum(input[index]) || isalpha(input[index])) {
      inputRead++;
      index++;
   }
}
