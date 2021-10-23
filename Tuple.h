
#ifndef PROJECT1_STARTER_CODE_TUPLE_H
#define PROJECT1_STARTER_CODE_TUPLE_H

#include <utility>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Tuple {
protected:


public:
    std::vector<std::string> values;
    bool operator< (const Tuple &rhs) const { // less that operator function from project guide
       return values < rhs.values;
    }

    explicit Tuple(vector<string> values) {
       this->values = std::move(values);
    }
    Tuple() {

    }

    void toString() {
       for (const string& value : values) {
          cout << value << ", ";
       }
       cout << endl;
    }

};


#endif //PROJECT1_STARTER_CODE_TUPLE_H
