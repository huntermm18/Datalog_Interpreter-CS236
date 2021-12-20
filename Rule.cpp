#include "Rule.h"
#include <iostream>
#include <utility>

Rule::Rule(Predicate* headPredicate, vector<Predicate*> bodyPredicates) {
   this->headPredicate = headPredicate;
   this->bodyPredicates = move(bodyPredicates);
}

void Rule::toString() {
   headPredicate->toString();
   cout << " :- ";
   for (unsigned int i = 0; i < bodyPredicates.size(); ++i) {
      bodyPredicates.at(i)->toString();
      if (i != bodyPredicates.size()-1) {
         cout << ",";
      }
   }
   cout << ".";
   // todo
}
