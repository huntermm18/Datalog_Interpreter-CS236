#include "Parser.h"
#include <utility>
using namespace std;

Parser::Parser(vector<Token*> tokens) {
   this->tokens = std::move(tokens);
}

bool Parser::parseProgram(){
   try {
      parseDatalogProgram();
      // cout << "Success!" << endl; // line needed for project 2
   }
   catch (Token* error){
      cout << "Failure!" << endl;
      cout << "  ";
      error->toString();
      return false;
   }
   return true;
}
void Parser::parseDatalogProgram() {

   //datalogProgram	->	SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryList EOF
   if(tokens.at(nextToken)->typeOfToken != TokenType::SCHEMES) {
      throw tokens.at(nextToken);
   }
   nextToken++;
   if(tokens.at(nextToken)->typeOfToken != TokenType::COLON) {
      throw tokens.at(nextToken);
   }
   nextToken++;
   parseScheme();
   parseSchemelist();
   if(tokens.at(nextToken)->typeOfToken != TokenType::FACTS) {
      throw tokens.at(nextToken);
   }
   nextToken++;
   if(tokens.at(nextToken)->typeOfToken != TokenType::COLON) {
      throw tokens.at(nextToken);
   }
   nextToken++;
   parseFactlist();
   if(tokens.at(nextToken)->typeOfToken != TokenType::RULES) {
      throw tokens.at(nextToken);
   }
   nextToken++;
   if(tokens.at(nextToken)->typeOfToken != TokenType::COLON) {
      throw tokens.at(nextToken);
   }
   nextToken++;
   parseRulelist();
   if(tokens.at(nextToken)->typeOfToken != TokenType::QUERIES) {
      throw tokens.at(nextToken);
   }
   nextToken++;
   if(tokens.at(nextToken)->typeOfToken != TokenType::COLON) {
      throw tokens.at(nextToken);
   }
   nextToken++;
   parseQuery();
   parseQuerylist();

   // check to see if at the end
   if (nextToken != (int)tokens.size() -1){
      throw tokens.at(nextToken);
   }
}
void Parser::parseSchemelist() {
   // schemeList	->	scheme schemeList | lambda
   if (tokens.at(nextToken)->typeOfToken == TokenType::ID) {
      parseScheme();
      parseSchemelist(); //todo double if statement?
   } // else do nothing because | lambda
}
void Parser::parseFactlist() {
   // factList	->	fact factList | lambda
   if (tokens.at(nextToken)->typeOfToken == TokenType::ID) {
      parseFact();
      parseFactlist();
   }
}
void Parser::parseRulelist() {
   // ruleList	->	rule ruleList | lambda
   if (tokens.at(nextToken)->typeOfToken == TokenType::ID) {
      parseRule();
      parseRulelist();
   }
}
void Parser::parseQuerylist(){
   // queryList	->	query queryList | lambda
   if (tokens.at(nextToken)->typeOfToken == TokenType::ID) {
      parseQuery();
      parseQuerylist();
   }
}
void Parser::parseScheme(){
   string id;
   Parameter* id2;
   vector<Parameter*> idList;
   // scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN
   if(tokens.at(nextToken)->typeOfToken != TokenType::ID) {
      throw tokens.at(nextToken);
   }

   id = tokens.at(nextToken)->value;
   nextToken++;

   if(tokens.at(nextToken)->typeOfToken != TokenType::LEFT_PAREN) {
      throw tokens.at(nextToken);
   }
   nextToken++;
   if(tokens.at(nextToken)->typeOfToken != TokenType::ID) {
      throw tokens.at(nextToken);
   }

   id2 = new Parameter(tokens.at(nextToken)->value);

   nextToken++;
   idList = parseIDlist();
   if(tokens.at(nextToken)->typeOfToken != TokenType::RIGHT_PAREN) {
      throw tokens.at(nextToken);
   }
   nextToken++;

   idList.insert(idList.begin(), id2);
   schemes.push_back(new Predicate(id, idList));
}
void Parser::parseFact(){
   //fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
   string id;
   Parameter* string;
   vector<Parameter*> idList;
   if(tokens.at(nextToken)->typeOfToken != TokenType::ID) {
      throw tokens.at(nextToken);
   }

   id = tokens.at(nextToken)->value;
   nextToken++;

   if(tokens.at(nextToken)->typeOfToken != TokenType::LEFT_PAREN) {
      throw tokens.at(nextToken);
   }
   nextToken++;
   if(tokens.at(nextToken)->typeOfToken != TokenType::STRING) {
      throw tokens.at(nextToken);
   }

   string = new Parameter(tokens.at(nextToken)->value);

   nextToken++;
   idList = parseStringlist();
   if(tokens.at(nextToken)->typeOfToken != TokenType::RIGHT_PAREN) {
      throw tokens.at(nextToken);
   }
   nextToken++;
   if(tokens.at(nextToken)->typeOfToken != TokenType::PERIOD) {
      throw tokens.at(nextToken);
   }
   nextToken++;

   idList.insert(idList.begin(), string);
   // domain
   for(int i = 0; i < (int)idList.size(); ++i) {
      domain.insert(idList.at(i)->p);
   }
   // end domain
   facts.push_back(new Predicate(id, idList));
}
void Parser::parseRule(){
   //rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
   Predicate* headPredicate;
   Predicate* predicate1;
   vector<Predicate*> bodyPredicates;

   headPredicate = parseHeadPredicate();


   if(tokens.at(nextToken)->typeOfToken != TokenType::COLON_DASH) {
      throw tokens.at(nextToken);
   }

   nextToken++;
   predicate1 = parsePredicate();
   bodyPredicates = parsePredicatelist();
   bodyPredicates.insert(bodyPredicates.begin(), predicate1);

   if(tokens.at(nextToken)->typeOfToken != TokenType::PERIOD) {
      throw tokens.at(nextToken);
   }
   nextToken++;
   rules.push_back(new Rule(headPredicate, bodyPredicates));
}
void Parser::parseQuery(){
   // query	        ->      predicate Q_MARK
   Predicate* predicate;

   predicate = parsePredicate();
   if(tokens.at(nextToken)->typeOfToken != TokenType::Q_MARK) {
      throw tokens.at(nextToken);
   }
   nextToken++;
   queries.push_back(predicate);
}
Predicate* Parser::parseHeadPredicate() {
   // headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
   vector<Parameter*> idList;
   string id;
   Parameter* id2;
   if(tokens.at(nextToken)->typeOfToken != TokenType::ID) {
      throw tokens.at(nextToken);
   }
   id = tokens.at(nextToken)->value;
   nextToken++;
   if(tokens.at(nextToken)->typeOfToken != TokenType::LEFT_PAREN) {
      throw tokens.at(nextToken);
   }
   nextToken++;
   if(tokens.at(nextToken)->typeOfToken != TokenType::ID) {
      throw tokens.at(nextToken);
   }
   id2 = new Parameter(tokens.at(nextToken)->value);
   nextToken++;
   idList = parseIDlist();
   if(tokens.at(nextToken)->typeOfToken != TokenType::RIGHT_PAREN) {
      throw tokens.at(nextToken);
   }
   nextToken++;
   idList.insert(idList.begin(), id2);
   return new Predicate(id, idList);
}
Predicate* Parser::parsePredicate() {
   // predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
   string id;
   Parameter* parameter1;
   vector<Parameter*> idList;

   if(tokens.at(nextToken)->typeOfToken != TokenType::ID) {
      throw tokens.at(nextToken);
   }
   id = tokens.at(nextToken)->value;
   nextToken++;
   if(tokens.at(nextToken)->typeOfToken != TokenType::LEFT_PAREN) {
      throw tokens.at(nextToken);
   }
   nextToken++;

   parameter1 = parseParameter();
   idList = parseParameterlist();
   idList.insert(idList.begin(), parameter1);
   if(tokens.at(nextToken)->typeOfToken != TokenType::RIGHT_PAREN) {
      throw tokens.at(nextToken);
   }
   nextToken++;
   return new Predicate(id, idList);
}
vector<Parameter*> Parser::parseIDlist() {
   // idList  	-> 	COMMA ID idList | lambda
   vector<Parameter*> idList;
   if (tokens.at(nextToken)->typeOfToken == TokenType::COMMA) {
      nextToken++;
      if(tokens.at(nextToken)->typeOfToken != TokenType::ID) {
         throw tokens.at(nextToken);
      }

      Parameter* id = new Parameter(tokens.at(nextToken)->value);
      nextToken++;

      idList = parseIDlist();
      idList.insert(idList.begin(), id);
      return idList;

   } // else nothing because lambda
   return idList;
}
vector<Predicate*> Parser::parsePredicatelist() {
   // predicateList	->	COMMA predicate predicateList | lambda
   vector<Predicate*> predicates;
   Predicate* predicate1;
   if (tokens.at(nextToken)->typeOfToken == TokenType::COMMA) {
      nextToken++;
      predicate1 = parsePredicate();
      predicates = parsePredicatelist();
      predicates.insert(predicates.begin(), predicate1);
   } // else nothing because lambda
   return predicates;
}
vector<Parameter*> Parser::parseParameterlist() {
   // parameterList	-> 	COMMA parameter parameterList | lambda
   vector<Parameter*> parameterList;
   Parameter* parameter1;
   if (tokens.at(nextToken)->typeOfToken == TokenType::COMMA) {
      nextToken++;
      parameter1 = parseParameter();
      parameterList = parseParameterlist();
      parameterList.insert(parameterList.begin(), parameter1);
   } // else nothing because lambda
   return parameterList;
}
vector<Parameter*> Parser::parseStringlist() {
   // stringList	-> 	COMMA STRING stringList | lambda
   vector<Parameter*> stringList;
   if (tokens.at(nextToken)->typeOfToken == TokenType::COMMA) {
      nextToken++;
      if(tokens.at(nextToken)->typeOfToken != TokenType::STRING) {
         throw tokens.at(nextToken);
      }
      Parameter* string = new Parameter(tokens.at(nextToken)->value);
      nextToken++;
      stringList = parseStringlist();
      stringList.insert(stringList.begin(), string);
      return stringList;
   } // else nothing because lambda
   return stringList;
}
Parameter* Parser::parseParameter() {
   // parameter	->	STRING | ID
   //Parameter* parameter;
   string id;
   string string;

   if(tokens.at(nextToken)->typeOfToken == TokenType::STRING) {
      id = parseID();
      nextToken++;
      return new Parameter(id);
   }
   else if (tokens.at(nextToken)->typeOfToken == TokenType::ID) {
      string = parseString();
      nextToken++;
      return new Parameter(string);
   }
   else {
      throw tokens.at(nextToken);
   }
}
string Parser::parseString() {
   return tokens.at(nextToken)->value;
}
string Parser::parseID() {
   return tokens.at(nextToken)->value;
}


void Parser::toString() {
   cout << "Schemes(" << schemes.size() << "):" << endl;
   for (int i = 0; i < (int)schemes.size(); ++i) {
      cout << "  ";
      schemes.at(i)->toString();
      cout << endl;
   }
   cout << "Facts(" << facts.size() << "):" << endl;
   for (unsigned int i = 0; i < facts.size(); ++i) {
      cout << "  ";
      facts.at(i)->toString();
      cout << "." <<endl;
   }
   cout << "Rules(" << rules.size() << "):" << endl;
   for (unsigned int i = 0; i < rules.size(); ++i) {
      cout << "  ";
      rules.at(i)->toString();
      cout << endl;
   }
   cout << "Queries(" << queries.size() << "):" << endl;
   for (unsigned int i = 0; i < queries.size(); ++i) {
      cout << "  ";
      queries.at(i)->toString();
      cout << "?" << endl;
   }
   cout << "Domain(" << domain.size() << "):" << endl;
   for (auto it = domain.begin(); it != domain.end(); ++it) {
      cout << "  " << *it << endl;
   }
}