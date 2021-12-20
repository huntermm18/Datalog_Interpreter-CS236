
#ifndef PROJECT1_STARTER_CODE_RELATION_H
#define PROJECT1_STARTER_CODE_RELATION_H

#include "Tuple.h"
#include "Header.h"
#include <set>


class Relation {
protected:
    vector<pair<int,int>> combineHeaders(Header* header2, Relation& returnRelation) const;
    static bool isJoinable(Tuple tuple1, Tuple tuple2, const vector<pair<int,int>>& matchIndexes);
    static Tuple combineTuples(Tuple tuple1, Tuple tuple2, const vector<pair<int,int>>& matchIndexes);


public:
    string name;
    Header* header;
    set<Tuple> rows; // recommended to not use pointers
    set<Tuple> rowsAddedByRules; // just for project 4 output


    Relation(string name, Header* header, set<Tuple> rows);
    Relation(string name, Header header, set<Tuple> rows);
    Relation();

//    select: parameters are index and value (relation column and value to select)
   void select (int index, const string& value);
//    • select: parameters are index and index (relation columns to select on same values)
   void select (int index, int index2);
//    • project: parameter is list of indices (the columns to keep)
   void project (const vector<int>& indexValues);
//    • rename: parameter is list of attributes (defines the new header)
   void rename (const vector<string>& attributes);
// The methods select, project, rename all return a new Relation object.


   Relation join (Relation r2);
   bool unionWith (const Relation& r2);

   void toString();
   void ruleEvaluationToString();
};


#endif //PROJECT1_STARTER_CODE_RELATION_H
