
#include "StringAutomaton.h"


int StringAutomaton::S0(const std::string& input) {
   if (input[index] == '\'') {
      inputRead++;
      index++;
      S1(input);
   }
   else {
      Serr();
   }

   return inputRead;
}

void StringAutomaton::S1(const std::string& input) {
   if(index < (int)input.size()) {
      if (input[index] == '\'') {
         inputRead++;
         index++;
         S4(input);
      }
      else if (input[index] == EOF) {
         inputRead--;
         index--;
         SetTokenTypeToVoid();
         return;
      }
      else {
         if (input[index] == '\n') {
            newLines++;
         }
         inputRead++;
         index++;
         S2(input);
      }
   }
   else {Serr();}
}

void StringAutomaton::S2(const std::string& input) {
   SetTokenTypeToVoid();
   if (input[index] == EOF) {
      inputRead--;
      index--;
      SetTokenTypeToVoid();
      return;
   }
   if (index < (int)input.size()) {
      if (input[index] == '\'') {
         inputRead++;
         index++;
         S3(input);
      }
      else {
         if (input[index] == '\n') {
            newLines++;
         }
         inputRead++;
         index++;
         S2(input);
      }

   }
}

void StringAutomaton::S3(const std::string& input) {
   SetTokenTypeToString();
   if (index < (int)input.size()) {
      if (input[index] == '\'') {
         inputRead++;
         index++;
         S2(input);
      }
   }
//   SetTokenTypeToVoid();
}

void StringAutomaton::S4(const std::string& input) {
   if (input[index] == EOF) {
      inputRead--;
      index--;
      SetTokenTypeToVoid();
      return;
   }

   if (index < (int)input.size()) {
      if (input[index] == '\'') {
         inputRead++;
         index++;
         S2(input);
//         S1(input);
      } else {
         return;
      }
   }
}