
#include "Interpreter.h"

void Interpreter::databaseToString() {
   database.toString();
}

Interpreter::Interpreter(DatalogProgram *program) {
   dataProgram = program;
   constructorHelper(); // makes relations and adds them to database
}

void Interpreter::constructorHelper() {
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
   //newRelation->toString();
   return newRelation;
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
