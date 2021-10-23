#ifndef PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
#define PROJECT1_STARTER_CODE_DATALOGPROGRAM_H

#include "Parser.h"
#include <set>
#include <vector>
using namespace std;


class DatalogProgram {

public:
    vector<Predicate*> schemes;
    vector<Predicate*> facts;
    vector<Predicate*> queries;
    vector<Rule*> rules;
    set<string> domain;

// public:
   DatalogProgram(vector<Predicate*> schemes,
      vector<Predicate*> facts,
      vector<Predicate*> queries,
      vector<Rule*> rules,
      set<string> domain);

    void toString();
};


#endif //PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
