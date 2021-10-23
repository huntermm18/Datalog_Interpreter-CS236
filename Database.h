
#ifndef PROJECT1_STARTER_CODE_DATABASE_H
#define PROJECT1_STARTER_CODE_DATABASE_H

// can't include datalog.h
#include "Relation.h"
#include <map>

class Database { // stores all the Relations build from schemes and facts

public:
    map<string, Relation*> tables; // name would be "snap", "csg" etc.

    void toString() { // for debugging
       for (pair<string, Relation*> t : tables) {
          cout << "name: " << t.first << endl << "[";
          t.second->toString();
          cout << "]" << endl;
       }
    }
};


#endif //PROJECT1_STARTER_CODE_DATABASE_H
