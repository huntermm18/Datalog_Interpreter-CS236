#include "Lexer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Parser.h"
#include "Interpreter.h"

using namespace std;


int main(int argc, char** argv) {

   // __________________write file to ss_________________________
   stringstream ss;
   ifstream ifs (argv[1], std::ifstream::binary);

   filebuf* pbuf = ifs.rdbuf();
   size_t size = pbuf->pubseekoff (0,std::ifstream::end,std::ifstream::in);
   pbuf->pubseekpos (0,std::ifstream::in);
   char* buffer=new char[size];
   pbuf->sgetn (buffer,size);
   ifs.close();
   ss.write (buffer,size);

   delete[] buffer;
   // ---------------------------------------------------------------

   auto* lexer = new Lexer();
   string fileToString = ss.str();
   lexer->Run(fileToString); // run file in lexer
   //cout << "Total Tokens = " << lexer->GetTokensVectorSize();

   auto* parser = new Parser(lexer->TokensWithoutComments()); // create parser and pass in the tokens vector
//   bool parseSuccess = parser->parseProgram();
//   if (parseSuccess) {
//      parser->toString();
//   }
   parser->parseProgram();
   auto* dataProgram = new DatalogProgram(parser->schemes, parser->facts, parser->queries, parser->rules, parser->domain);
   auto* interpreter = new Interpreter(dataProgram);
   //interpreter->databaseToString(); // for debugging
   //interpreter->queriesToString(); // for debugging
   interpreter->evaluateRules();
   interpreter->evaluateAllQueries();


    delete lexer;

    return 0;
}