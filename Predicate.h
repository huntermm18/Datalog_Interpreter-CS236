#ifndef PROJECT1_STARTER_CODE_PREDICATE_H
#define PROJECT1_STARTER_CODE_PREDICATE_H

#include "Parameter.h"
#include <vector>

class Predicate {

public:
    void toString();
    string id;
    vector<Parameter*> parameters;
    Predicate(string id, vector<Parameter*> parameters);

};

#endif //PROJECT1_STARTER_CODE_PREDICATE_H
