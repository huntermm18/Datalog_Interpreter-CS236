
#ifndef PROJECT1_STARTER_CODE_HEADER_H
#define PROJECT1_STARTER_CODE_HEADER_H

#include <utility>
#include <vector>
#include <string>

class Header {
public:
    vector<string> attributes;

    explicit Header(vector<std::string> attributes) {
       this->attributes = std::move(attributes);
    }
    Header()= default;

    void toString() {
       for (string s : attributes) {
          cout << s << ", ";
       }
       cout << endl;
    }
};


#endif //PROJECT1_STARTER_CODE_HEADER_H
