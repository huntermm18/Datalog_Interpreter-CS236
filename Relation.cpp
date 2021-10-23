//
// Created by hunte on 10/12/2021.
//

#include "Relation.h"

#include <utility>

void Relation::toString() {
   cout << name << ":" << endl;

   header->toString();

   for(Tuple t : rows) {
    t.toString();
    }
}

Relation::Relation(string name, Header* header, set<Tuple> rows) {
   this->name = std::move(name);
   this->header = header;
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
   Tuple newTuple;
   for (int index : indexValues) {
      newHeader->attributes.push_back(header->attributes.at(index));
      for (Tuple tuple : rows) {
         newTuple.values.push_back(tuple.values.at(index));
      }
      newRows.insert(newRows.begin(), newTuple);
   }
   this->header = newHeader;
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