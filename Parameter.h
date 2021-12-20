#ifndef PROJECT1_STARTER_CODE_PARAMETER_H
#define PROJECT1_STARTER_CODE_PARAMETER_H

#include <string>
#include <utility>
using namespace std;


class Parameter {
    // could be STRING or ID

public:

    string p;
    bool isConstant;

    explicit Parameter(string id) {
       p = std::move(id);
       if (p.at(0) == '\'') {
          isConstant = true;
       }
       else {
          isConstant = false;
       }
    }
};


#endif //PROJECT1_STARTER_CODE_PARAMETER_H
