#ifndef PROJECT1_STARTER_CODE_GRAPH_H
#define PROJECT1_STARTER_CODE_GRAPH_H

#include <set>
#include <map>
#include <vector>
#include "Rule.h"
#include <iostream>

using namespace std;

class Graph {
public:


    explicit Graph(vector<Rule*>& rules);

    map<int, set<int>> adjacencyList;
    map<int, set<int>> reverseGraphAdjacencyList;
    set<int> visited;
    vector<int> postorderList;
   //set<Node*> nodes;
   //set<Node*> reverseGraphNodes;
   vector<set<int>> scc;
   set<int> tempSCC;

   void depthFirstSearchOnReverse(int index); // create two. one for post order and one for scc
   void depthFirstSearchOnOriginal(int index);
   void depthFirstSearchForrest();
   vector<set<int>> dfsForrestForSCCs();

   void dependencyGraphToString();
   vector<int> getRuleIndexFromVector(Predicate* predicate);

protected:
    vector<Rule*> rules;
};


#endif //PROJECT1_STARTER_CODE_GRAPH_H
