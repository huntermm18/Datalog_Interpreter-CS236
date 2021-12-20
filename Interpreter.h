
#ifndef PROJECT1_STARTER_CODE_INTERPRETER_H
#define PROJECT1_STARTER_CODE_INTERPRETER_H

#include "DatalogProgram.h"
#include "Relation.h"
#include "Database.h"
#include "Graph.h"

class Interpreter {

protected:
    DatalogProgram* dataProgram{};
    Database database;

public:
    map<string,int> variables;
    vector<string> variableOrderList;

    explicit Interpreter(DatalogProgram* program);
    Interpreter() = default;
    void evaluateQuery(Predicate* query);
    void evaluateAllQueries();
    void queriesToString();

    Relation evaluatePredicateBasic(const Predicate& p);
    Relation* evaluatePredicate(const Predicate& p);

    void schemesToRelationsHelper();
    void factsToTuplesHelper();
    void evaluateRules();
    bool evaluateOneRule(Rule* rule);
    vector<string> getAttributesFromRelation(const string& name);
    Relation* getRelationByName(const string& name);

    static vector<int> createIndexVecForProjectOnNewRelation(Relation* relation, Predicate* headPredicate);

};


#endif //PROJECT1_STARTER_CODE_INTERPRETER_H
