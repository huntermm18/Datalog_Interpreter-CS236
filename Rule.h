#ifndef PROJECT1_STARTER_CODE_RULE_H
#define PROJECT1_STARTER_CODE_RULE_H

#include "Predicate.h"
#include <vector>

class Rule {
protected:


public:
    Rule(Predicate* headPredicate, vector<Predicate*> bodyPredicates);
    void toString();
    Predicate* headPredicate;
    vector<Predicate*> bodyPredicates;

};


#endif //PROJECT1_STARTER_CODE_RULE_H
