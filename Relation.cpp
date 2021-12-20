#include "Relation.h"

#include <utility>

void Relation::toString() {
   cout << name << ":" << endl;
   header->toString();

   for(Tuple t : rows) {
      cout << "  ";
      t.toString();
   }
}

void Relation::ruleEvaluationToString() {
   for(Tuple t : rowsAddedByRules) {
      if (t.values.size() == 0) {
         break;
      }
      cout << "  ";
      //t.toString();
      for (unsigned int j = 0; j < header->attributes.size(); ++j) {
         cout << header->attributes.at(j) << "=" << t.values.at(j);
         if (j != header->attributes.size()-1) {
            cout << ", ";
         }
      }
      cout << endl;
   }
}

Relation::Relation(string name, Header* header, set<Tuple> rows) {
   this->name = std::move(name);
   this->header = header;
   this->rows = std::move(rows);
}

Relation::Relation() {
   set<Tuple> rows;
   this->name = "";
}

Relation::Relation(string name, Header header, set<Tuple> rows) {
   this->name = std::move(name);
   this->header = &header;
   this->rows = std::move(rows);
}

void Relation::select (int index, const string& value) {
   set<Tuple> newRows;
   vector<string> newSaveStrings;
   for (Tuple row : rows) {
      if (row.values.at(index) == value) {
         newRows.insert(newRows.begin(), row);
      }
   }
   this->rows = newRows;

   //return new Relation(name, header, newRows);
}
void Relation::select (int index, int index2) {
   set<Tuple> newRows;
   for (Tuple row : rows) {
      if (row.values.at(index) == row.values.at(index2)) {
         newRows.insert(newRows.begin(), row);
      }
   }
   this->rows = newRows;
   //return new Relation(name, header, newRows);
}
void Relation::project (const vector<int>& indexValues) {
   auto *newHeader = new Header;
   set<Tuple> newRows;

   for (int index : indexValues) {
      newHeader->attributes.push_back(header->attributes.at(index));
   }

   for (Tuple tuple : rows) {
      auto* newTuple = new Tuple;
      for (int index : indexValues) {
         newTuple->values.push_back(tuple.values.at(index));
      }
      newRows.insert(newRows.begin(), *newTuple);
      delete newTuple;
   }

   auto* newHeader3 = new Header;
   newHeader3->attributes = newHeader->attributes;
   this->header = newHeader3;
   this->rows = newRows;
   //return new Relation(name, newHeader, newRows);
}

void Relation::rename (const vector<string>& attributes) {
   auto *newHeader = new Header;
   for (const string& attribute : attributes) {
      newHeader->attributes.push_back(attribute);
   }
   this->header = newHeader;
   //return new Relation(name, newHeader, rows);
}

vector<pair<int,int>> Relation::combineHeaders(Header* header2, Relation& returnRelation) const {
   vector<pair<int,int>> matchAttributes;
   pair<int,int> toPushPair;
   bool match = false;
   for (unsigned int i = 0; i < header2->attributes.size(); ++i) {
      match = false;
      for (unsigned int j = 0; j < header->attributes.size(); ++j) {

         if (header2->attributes.at(i) == header->attributes.at(j)) {
            match = true;
            toPushPair.first = j;
            toPushPair.second = i;
            matchAttributes.push_back(toPushPair); // save attribute where there was a match
         }
      }
      if (!match) {
         // not match so add the element of header2 to the end of header 1
         returnRelation.header->attributes.push_back(header2->attributes.at(i));
      }
   }
   return matchAttributes;
}

bool Relation::isJoinable(Tuple tuple1, Tuple tuple2, const vector<pair<int,int>>& matchIndexes) {
   for (pair<int,int> matchIndex : matchIndexes) {
      if (tuple1.values.at(matchIndex.first) != tuple2.values.at(matchIndex.second)) {
         return false;
      }
   }
   return true;
}
Tuple Relation::combineTuples(Tuple tuple1, Tuple tuple2, const vector<pair<int,int>>& matchIndexes) {
   Tuple newTuple = std::move(tuple1);
   bool match;
   for (unsigned int i = 0; i < tuple2.values.size(); ++i) {
      match = false;
      for (pair<int,int> matchIndex : matchIndexes) {
         if ((int)i == matchIndex.second) {
            match = true;
         }
      }
      if(!match) {
         // the i element in tuple 2 isn't one that is already in tuple1 so it is added
         newTuple.values.push_back(tuple2.values.at(i));
      }
   }
   return newTuple;
}


Relation Relation::join (Relation r2) {

   Relation returnRelation;
   Header* newHeader = new Header;
   newHeader->attributes = this->header->attributes;
   returnRelation.header = newHeader;

   //combine headers
   vector<pair<int,int>> matchIndexes = combineHeaders(r2.header, returnRelation);

   set<Tuple> newRows;
   bool canJoin;

   for (const Tuple& tuple1 : rows) {
      for (const Tuple& tuple2 : r2.rows) {
         canJoin = isJoinable(tuple1, tuple2, matchIndexes);
         if (canJoin) {
            Tuple newTuple = combineTuples(tuple1, tuple2, matchIndexes);
            newRows.insert(newTuple);

         }
      }
   }

   //this->rows = newRows;
   returnRelation.rows = newRows;
   return returnRelation;
}

bool Relation::unionWith (const Relation& r2) {
   bool madeUpdate = false;
   for (unsigned int i = 0; i < header->attributes.size(); ++i) { // compatible check. Can delete
      if (header->attributes.at(i) != r2.header->attributes.at(i)) {
         cout << "union Error: Headers don't match" << endl;
      }
   }
   for (const Tuple& tuple : r2.rows) {
      if (rows.insert(tuple).second) {
         madeUpdate = true;
         rowsAddedByRules.insert(tuple); // for project 4
      }
   }
   return madeUpdate;
}


