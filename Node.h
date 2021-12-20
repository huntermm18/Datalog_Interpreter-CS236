
#ifndef PROJECT1_STARTER_CODE_NODE_H
#define PROJECT1_STARTER_CODE_NODE_H

#include <set>
#include <map>
#include <vector>
#include "Rule.h"
#include <iostream>

class Node {
public:
    int index;
    set<int> adjacencyList;
    bool visited;

    Node(int index) {
       this->index = index;
    }
};

#endif //PROJECT1_STARTER_CODE_NODE_H
