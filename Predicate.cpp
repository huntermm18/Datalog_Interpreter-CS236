#include "Predicate.h"
#include <iostream>
using namespace std;

Predicate::Predicate(string id, vector<Parameter*> parameters) {
   this->id = id;
   this->parameters = parameters;
}

void Predicate::toString() {
   cout << id << "(";
   for (unsigned int i = 0; i < parameters.size(); ++i) {
      cout << parameters.at(i)->p;
      if (i != parameters.size() -1) {
         cout << ",";
      }
   }
   cout << ")";
}
