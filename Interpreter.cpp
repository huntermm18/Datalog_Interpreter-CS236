#include "Interpreter.h"
#include <iostream>


void Interpreter::schemesToRelationsHelper() {
   // make relation for each scheme and add to database
   for (auto & scheme : dataProgram->schemes) {

      // create vector<string> attributes from scheme parameter vector
      vector<string> attributes;
      for (auto & parameter : scheme->parameters) {
         attributes.push_back(parameter->p);
      }

      auto* newHeader = new Header(attributes);
      string name = scheme->id;
      set<Tuple> rows;
      auto* newRelation = new Relation(name, newHeader, rows);

      //add the new relation to the interpreter's database
      database.tables.insert(std::pair<string, Relation*>(name, newRelation));

   }
}
void Interpreter::factsToTuplesHelper() {
   // make tuple for each fact and add to appropriate relation in the database
   for (auto & fact : dataProgram->facts) {

      // make vector "values" from fact parameter vector
      vector<string> values;
      for (auto & parameter : fact->parameters) {
         values.push_back(parameter->p);
      }

      // add to appropriate relation in database
      auto* newTuple = new Tuple(values);
      for (auto & table : database.tables) {
         if (table.first == fact->id) {
            table.second->rows.insert(table.second->rows.begin(), *newTuple);
         }
      }
   }
}

Interpreter::Interpreter(DatalogProgram *program) {
   dataProgram = program;

   // make relation for each scheme and add to database
   Interpreter::schemesToRelationsHelper();

   // make tuple for each fact and add to appropriate relation in the database
   Interpreter::factsToTuplesHelper();
}

Relation Interpreter::evaluatePredicateBasic(const Predicate& p) {

   Relation returnRelation = *database.tables.at(p.id);
   vector<string> renameVec;

   for (int i = 0 ; i < (int)p.parameters.size(); ++i) {
      if (p.parameters.at(i)->isConstant) {
         returnRelation.select(i, p.parameters.at(i)->p);
      }
   }
      for (Parameter* parameter : p.parameters) {
      renameVec.push_back(parameter->p);
   }

   returnRelation.rename(renameVec);
   return returnRelation;
}

Relation* Interpreter::evaluatePredicate(const Predicate& p) {
   // create the new relation to be returned
   Relation* oldRelation = database.tables.at(p.id);
   auto* newRelation = new Relation(oldRelation->name, oldRelation->header, oldRelation->rows);

   //see flowchart
   for (int i = 0 ; i < (int)p.parameters.size(); ++i) {
      if (p.parameters.at(i)->isConstant) {
         newRelation->select(i, p.parameters.at(i)->p);
      }
      else {
         if (variables.find(p.parameters.at(i)->p) == variables.end()) { // var not seen yet, mark
            variables.insert(pair<string,int>(p.parameters.at(i)->p, i)); // add to map
            variableOrderList.push_back(p.parameters.at(i)->p); // add index to list for printing later
         }
         else { // var seen so do selection
            newRelation->select(i, variables.at(p.parameters.at(i)->p));
         }
      }
   }
   return newRelation;
}

vector<int> Interpreter::createIndexVecForProjectOnNewRelation (Relation* relation, Predicate* headPredicate) {
   vector<int> returnIndexes;

   for (auto & parameter : headPredicate->parameters) {
      for (unsigned int j = 0; j < relation->header->attributes.size(); ++j) {
         if (relation->header->attributes.at(j) == parameter->p) {
            returnIndexes.push_back(j);
         }
      }
   }
   return returnIndexes;
}

vector<string> Interpreter::getAttributesFromRelation(const string& name) {
   return database.tables.at(name)->header->attributes;
}

Relation* Interpreter::getRelationByName(const string& name) {
   return database.tables.at(name);
}

bool Interpreter::evaluateOneRule(Rule* rule) {
   // evaluate the predicates on the right-hand side of the rule
   // join the relations that result
   // project the columns that appear in the head predicate
   // rename the relation to make it union-compatible (optional?)
   // union with the relation in the database

   variableOrderList.clear();
   variables.clear();

   vector<Relation> relations;
   bool madeChange = false;

   rule->toString();
   cout  << endl;

   for (Predicate* p : rule->bodyPredicates) {
      Relation newRelation = evaluatePredicateBasic(*p);
      relations.push_back(newRelation);
   }

   Relation finalRelation;
   finalRelation = relations[0];

   for (unsigned int i = 1; i < relations.size(); ++i) { // skip 0
      finalRelation = finalRelation.join(relations.at(i));
   }

   //project the columns of the head predicate onto the relation
   vector<int> indexesForProject = createIndexVecForProjectOnNewRelation(&finalRelation, rule->headPredicate);
   finalRelation.project(indexesForProject); // figure out indexes to project


   //rename each attribute in the relation to match the relation in the database that matches the head predicate
   string name = rule->headPredicate->id;
   vector<string> newHeaderNames = getAttributesFromRelation(name);
   finalRelation.rename(newHeaderNames);
   //finalRelation.toString(); // debugging

   //union
   Relation* updateRelation = getRelationByName(name);
   madeChange = updateRelation->unionWith(finalRelation);
   updateRelation->ruleEvaluationToString(); // for project 4
   updateRelation->rowsAddedByRules.clear(); // for project 4

   return madeChange;
}

void Interpreter::evaluateRules() {

   Graph graph(dataProgram->rules);
   graph.dependencyGraphToString();
   graph.depthFirstSearchForrest();
   vector<set<int>> scc = graph.dfsForrestForSCCs();
   int numPasses;
   set<int>::iterator it;

   cout << "Rule Evaluation" << endl;
   for (const set<int>& currentSCC : scc) {
      cout << "SCC: ";
      for(it = currentSCC.begin(); it != currentSCC.end();) {
         cout << "R" << *it;
         if (++it != currentSCC.end()) {
            cout << ",";
         }
      }
      cout << endl;

      numPasses = 0;
      bool rulesUpdated = true;
      while (rulesUpdated) {
         numPasses++;
         rulesUpdated = false;
         for (int ruleNum : currentSCC) {
            Rule* currentRule = dataProgram->rules.at(ruleNum);
            if(evaluateOneRule(currentRule)) {
               rulesUpdated = true;
            }
         }
         bool isDependent = true;
         if (currentSCC.size() == 1) { // check to see if the scc is only one rule and is not dependent on itself
            Rule* currentRule = dataProgram->rules.at(*currentSCC.begin());
            isDependent = false;
            for (Predicate* bodyPredicate : currentRule->bodyPredicates) {
               if (bodyPredicate->id == currentRule->headPredicate->id) {
                  isDependent = true;
               }
            }
         }
         if (!isDependent) { // if the rule isn't dependent stop looping after first pass
            rulesUpdated = false;
         }
      }
      cout << numPasses << " passes: ";
      for(it = currentSCC.begin(); it != currentSCC.end();) {
         cout << "R" << *it;
         if (++it != currentSCC.end()) {
            cout << ",";
         }
      }
      cout << endl;
   }
}

void Interpreter::evaluateQuery(Predicate* query) {
   // create a new relation by evaluating the predicate with the query
   Relation* newRelation = evaluatePredicate(*query);

   // check to see if there is anything in the new relation
   if (!newRelation->rows.empty()) {
      query->toString();
      cout << "? Yes(" << newRelation->rows.size() << ")" << endl;
      for (Tuple row : newRelation->rows) {
         map<string, int>::iterator it;
         if (!variableOrderList.empty()) { //print spaces only if there are vars to print
            cout << "  ";
         }
         for (const auto& var : variableOrderList) {
            cout << var << "=" << row.values.at(variables.at(var));
            if (var != variableOrderList.back()) {
               cout << ", ";
            }
         }
         if (!variableOrderList.empty()){
            cout << endl; // print new line only if there are vars to print
         }
      }
   }
   else {
      query->toString();
      cout << "? No" << endl;
   }

   variables.clear(); // reset member vars so they don't add onto each other
   variableOrderList.clear();
}

void Interpreter::evaluateAllQueries() {
   // runs evaluateQuery on each query in query list
   cout << endl << "Query Evaluation" << endl;
   for (Predicate* query : dataProgram->queries) {
      evaluateQuery(query);
   }
}

void Interpreter::queriesToString() {
   cout << "QUERIES:" << endl;
   for (Predicate* query: dataProgram->queries) {
      query->toString();
      cout << endl;
   }
}
