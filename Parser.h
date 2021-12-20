#ifndef PROJECT1_STARTER_CODE_PARSER_H
#define PROJECT1_STARTER_CODE_PARSER_H

#include "Rule.h"
#include "Lexer.h"
#include <set>
#include <iostream>
using namespace std;

class Parser {

protected:

    int nextToken = 0;
    vector<Token*> tokens;

public:

    vector<Predicate*> schemes;
    vector<Predicate*> facts;
    vector<Predicate*> queries;
    vector<Rule*> rules;
    set<string> domain;

    explicit Parser(vector<Token *> tokens);
    bool parseProgram();

    void parseDatalogProgram();
    void parseSchemelist();
    void parseFactlist();
    void parseRulelist();
    void parseQuerylist();
    void parseScheme();
    void parseFact();
    void parseRule();
    void parseQuery();
    Predicate* parseHeadPredicate();
    Predicate* parsePredicate();
    vector<Parameter*> parseIDlist();
    vector<Predicate*> parsePredicatelist();
    vector<Parameter*> parseParameterlist();
    vector<Parameter*> parseStringlist();
    Parameter* parseParameter();
    string parseString();
    string parseID();

    void toString();

};

#endif //PROJECT1_STARTER_CODE_PARSER_H
