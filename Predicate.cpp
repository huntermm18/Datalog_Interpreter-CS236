#include "Predicate.h"
#include <iostream>
#include <utility>
using namespace std;

Predicate::Predicate(string id, vector<Parameter*> parameters) {
   this->id = move(id);
   this->parameters = move(parameters);
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
