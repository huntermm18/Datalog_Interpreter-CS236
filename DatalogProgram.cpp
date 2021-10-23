#include "DatalogProgram.h"

#include <utility>

DatalogProgram::DatalogProgram(vector<Predicate *> schemes,
                               vector<Predicate *> facts,
                               vector<Predicate *> queries,
                               vector<Rule *> rules,
                               set<string> domain) {
   this->schemes = std::move(schemes);
   this->facts = std::move(facts);
   this->rules = std::move(rules);
   this->queries = std::move(queries);
   this->domain = std::move(domain);
}



void DatalogProgram::toString() {
   cout << "Schemes(" << schemes.size() << "):" << endl;
   for (int i = 0; i < (int)schemes.size(); ++i) {
      cout << "  ";
      schemes.at(i)->toString();
      cout << endl;
   }
   cout << "Facts(" << facts.size() << "):" << endl;
   for (unsigned int i = 0; i < facts.size(); ++i) {
      cout << "  ";
      facts.at(i)->toString();
      cout << "." <<endl;
   }
   cout << "Rules(" << rules.size() << "):" << endl;
   for (unsigned int i = 0; i < rules.size(); ++i) {
      cout << "  ";
      rules.at(i)->toString();
      cout << endl;
   }
   cout << "Queries(" << queries.size() << "):" << endl;
   for (unsigned int i = 0; i < queries.size(); ++i) {
      cout << "  ";
      queries.at(i)->toString();
      cout << "?" << endl;
   }
   cout << "Domain(" << domain.size() << "):" << endl;
   for (auto it = domain.begin(); it != domain.end(); ++it) {
      cout << "  " << *it << endl;
   }

}