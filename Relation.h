
#ifndef PROJECT1_STARTER_CODE_RELATION_H
#define PROJECT1_STARTER_CODE_RELATION_H

#include "Tuple.h"
#include "Header.h"
#include <set>


class Relation {
public:
    string name;
    Header* header;
    set<Tuple> rows; // recommended to not use pointers


    Relation(string name, Header* header, set<Tuple> rows);

//    select: parameters are index and value (relation column and value to select)
   void select (int index, const string& value);
//    • select: parameters are index and index (relation columns to select on same values)
   void select (int index, int index2);
//    • project: parameter is list of indices (the columns to keep)
   void project (const vector<int>& indexValues);
//    • rename: parameter is list of attributes (defines the new header)
   void rename (const vector<string>& attributes);
// The methods select, project, rename all return a new Relation object.


   // void addTuple(Tuple);
   void toString();

};


#endif //PROJECT1_STARTER_CODE_RELATION_H
