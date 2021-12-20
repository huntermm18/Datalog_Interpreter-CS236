
#include "Graph.h"

/*
 * steps:
 * 1 - create dependency graph
 * 2 - construct reverse graph
 * 3 - run dfs forest on reverse graph to get postorder
 * 4 - run dfs forest on original graph to get SCCs
 */

vector<int> Graph::getRuleIndexFromVector(Predicate* predicate) {
   vector<int> returnIndexes;
   for (unsigned int i = 0; i < rules.size(); ++i) {
      if (rules.at(i)->headPredicate->id == predicate->id) {
         //cout << "returning: " << i << endl;
         returnIndexes.push_back(i);
      }
   }
   return returnIndexes;
}
Graph::Graph(vector<Rule *>& rules) {
   this->rules = rules;
   // create nodes for each rule in the vector
   for (unsigned int i = 0; i < rules.size(); ++i) {
      pair<int,set<int>> insertPair;
      insertPair.first = i;
      adjacencyList.insert(insertPair);
      reverseGraphAdjacencyList.insert(insertPair);
   }

   for (unsigned int i = 0; i < rules.size(); ++i) {
      Rule* currentRule = rules.at(i);

      for (Predicate* predicate : currentRule->bodyPredicates) {
         //int ruleIndex = getRuleIndexFromVector(predicate);
         vector<int> ruleIndexes = getRuleIndexFromVector(predicate);
         for (int index : ruleIndexes) {
            adjacencyList.at(i).insert(index);
            reverseGraphAdjacencyList.at(index).insert(i);
         }
      }
   }
}



void Graph::dependencyGraphToString() {
   cout << "Dependency Graph" << endl;

   for (pair<int,set<int>> node : adjacencyList) {
      cout << "R" << node.first << ":";
      set<int>::iterator it;
      for (it = node.second.begin(); it != node.second.end();) {
         cout << "R" << *it;
         if(++it != node.second.end()) {
            cout << ",";
         }
      }
      cout << endl;
   }
   cout << endl;
}

void Graph::depthFirstSearchForrest() {
   //vector<int> visited;
   int currentNode = 0;
   while(visited.size() < adjacencyList.size()) {
      if (visited.find(currentNode) == visited.end()) {
         depthFirstSearchOnReverse(currentNode);
      }
      ++currentNode;
   }
   //tempSCC.clear();
   visited.clear();
//   for (int num : postorderList) {
//      cout << num << ",";
//   } cout << endl;
}

void Graph::depthFirstSearchOnReverse(int index) {
   // postorder
   bool notInVisitedList = visited.insert(index).second; // add current node to the visited list
   if(!notInVisitedList) {
      return;
   }
   for (int edge : reverseGraphAdjacencyList.at(index)) {
      if (visited.find(edge) == visited.end()) { // if the edge hasn't been visited yet
         depthFirstSearchOnReverse(edge);
         //break;
      }
   }
   postorderList.push_back(index);
   //tempSCC.insert(index);
}
void Graph::depthFirstSearchOnOriginal(int index) {
   // postorder
   bool notInVisitedList = visited.insert(index).second; // add current node to the visited list
   if(!notInVisitedList) {
      return;
   }
   for (int edge : adjacencyList.at(index)) {
      if (visited.find(edge) == visited.end()) { // if the edge hasn't been visited yet
         depthFirstSearchOnOriginal(edge);
         //break;
      }
   }
   //postorderList.push_back(index);
   tempSCC.insert(index);
}

vector<set<int>> Graph::dfsForrestForSCCs() {

   int currentNode;
   while(visited.size() < adjacencyList.size()) {
      currentNode = postorderList.back();
      if (visited.find(currentNode) == visited.end()) {
         depthFirstSearchOnOriginal(currentNode);
         scc.push_back(tempSCC);
         tempSCC.clear();
      }
      postorderList.pop_back();
   }
   tempSCC.clear();
   visited.clear();

//   for (set<int> sccCurrent : scc) {
//      cout << "scc:";
//      for (int num : sccCurrent) {
//         cout << num << ",";
//      }
//      cout << endl;
//   }

   return scc;
}
