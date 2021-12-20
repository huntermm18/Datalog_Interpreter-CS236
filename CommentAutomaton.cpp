#include "CommentAutomaton.h"
#include <string>
int CommentAutomaton::S0(const std::string& input) {
   if (input[index] == '#') {
      inputRead++;
      index++;
      S1(input);
   }
   return inputRead;
}

void CommentAutomaton::S1(const std::string& input) {
   if (index < (int)input.size()) {
      if (input[index] != '|') {
         inputRead++;
         index++;
         S2(input);
      }
      else if (input[index] == '|'){
         inputRead++;
         index++;
         S3(input);
      }
   }
}

void CommentAutomaton::S2(const std::string& input) {
   if (index < (int)input.size()) {
      if (input[index] == '\n') {
//         newLines++;
      }
      else {
         inputRead++;
         index++;
         S2(input);
      }
   }
}
void CommentAutomaton::S3(const std::string& input) {
   if (input[index] == '\n') {
      newLines++;
   }
   SetTokenTypeToVoid();
   if (index < (int)input.size()) {
      if (input[index] == '|') {
         inputRead++;
         index++;
         S4(input);
      }
      else {
         inputRead++;
         index++;
         S3(input);
      }
   }
}
void CommentAutomaton::S4(const std::string& input) {
   if (input[index] == '\n') {
      newLines++;
   }
   if (index < (int)input.size()) {
      if (input[index] == '#') {
         inputRead++;
         index++;
         SetTokenTypeToComment();
         return;
      }
      else {
         inputRead++;
         index++;
         S3(input);
      }
   }
}