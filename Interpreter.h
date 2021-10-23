
#ifndef PROJECT1_STARTER_CODE_INTERPRETER_H
#define PROJECT1_STARTER_CODE_INTERPRETER_H

#include "DatalogProgram.h"
#include "Relation.h"
#include "Database.h"

class Interpreter { //not required class

protected:
    DatalogProgram* dataProgram{};
    Database database;

public:
    map<string,int> variables;
    vector<string> variableOrderList;

    explicit Interpreter(DatalogProgram* program);
    void constructorHelper();
    Interpreter() = default;
    void evaluateQuery(Predicate* query);
    void evaluateAllQueries();
    void databaseToString();
    void queriesToString();

    Relation* evaluatePredicate(const Predicate& p); // optional recommended function

//    constants are Datalog STRINGs and variables are Datalog IDs:

//    for each scheme ‘s’
//    create a relation using name and parameter values from ‘s’
//    for each fact ‘f’
//    make a tuple ‘t’ using the values from ‘f’
//    add ‘t’ to relation with the same name as ‘f’
//    for each query ‘q’
//    get the relation ‘r’ with the same name as the query ‘q’
//    select for each constant in the query ‘q’
//    select for each pair of matching variables in ‘q’
//    project using the positions of the variables in ‘q’
//    rename to match the names of variables in ‘q’
//    print the resulting relation

};


#endif //PROJECT1_STARTER_CODE_INTERPRETER_H
