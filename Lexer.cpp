#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "MatcherAutomaton.h"
#include "IdentifierAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include <iostream>

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
   for (auto p : automata) {
      delete p;
   }
   automata.clear();
   for (auto p : tokens) {
      delete p;
   }
   tokens.clear();
}

int Lexer::GetTokensVectorSize() {
   return tokens.size();
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new MatcherAutomaton("Queries", TokenType::QUERIES));
    automata.push_back(new MatcherAutomaton("Rules", TokenType::RULES));
    automata.push_back(new MatcherAutomaton(",", TokenType::COMMA));
    automata.push_back(new MatcherAutomaton(".", TokenType::PERIOD));
    automata.push_back(new MatcherAutomaton("?", TokenType::Q_MARK));
    automata.push_back(new MatcherAutomaton("(", TokenType::LEFT_PAREN));
    automata.push_back(new MatcherAutomaton(")", TokenType::RIGHT_PAREN));
    automata.push_back(new MatcherAutomaton("*", TokenType::MULTIPLY));
    automata.push_back(new MatcherAutomaton("+", TokenType::ADD));
    automata.push_back(new MatcherAutomaton("Schemes", TokenType::SCHEMES));
    automata.push_back(new MatcherAutomaton("Facts", TokenType::FACTS));
    automata.push_back(new MatcherAutomaton("Rules", TokenType::RULES));
    automata.push_back(new IdentifierAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());

}

void Lexer::Run(std::string& input) {
   lineNumber = 1;
   while (!input.empty()) {
      maxRead = 0;
      maxAutomaton = automata.at(0);

      if (!input.empty()) { //fixme
         while (isspace(input[0])) {
            //if (input[0] == '\t') {input.erase(input.begin());}
            if (input[0] == '\n') {
               lineNumber++;
            }
            input.erase(input.begin());
            if (input[0] == '\n') {
               input.erase(input.begin());
               lineNumber++;
            }
         }
      }


      for (unsigned int i = 0; i < automata.size(); ++i) {
         automata[i]->inputRead = automata[i]->Start(input);
         if (automata[i]->inputRead > maxRead) {
            maxRead = automata[i]->inputRead;
            maxAutomaton = automata[i];
         }
      }
      if (maxRead > 0) {
         Token *newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber);
         lineNumber += maxAutomaton->NewLinesRead();
         tokens.push_back(newToken);
      }

         // No automaton accepted input
         // Create single character undefined token
      else {
         if (!input.empty()) {
            maxRead = 1;
            string firstChar = input.substr(0, 1); // not sure. first char?
            Token *newToken = new Token(TokenType::UNDEFINED, firstChar, lineNumber);
            tokens.push_back(newToken);
         }
      }
      //remove maxRead characters from input
      input.erase(input.begin() + 0, input.begin() + maxRead); // check
   }
   //add eof token to token vector
   Token *EOFToken = new Token(TokenType::EOF_TYPE, "", lineNumber);
   tokens.push_back(EOFToken);

   //to string function no longer needed
//   for (unsigned int i = 0; i < tokens.size(); ++i) {
//      tokens.at(i)->toString();
//   }
}

vector<Token*> Lexer::TokensWithoutComments() {
   vector<Token*> returnVector;
   for (auto & token : tokens) {
      if (token->typeOfToken != TokenType::COMMENT) {
         returnVector.push_back(token);
      }
   }
   return returnVector;
}