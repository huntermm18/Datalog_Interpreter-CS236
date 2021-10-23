#include "ColonDashAutomaton.h"

int ColonDashAutomaton::S0(const std::string& input) {
    if (input[index] == ':') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
    return inputRead; //fixme (was 1 and worked?)
}

void ColonDashAutomaton::S1(const std::string& input) {
    if (input[index] == '-') {
        inputRead++;
    }
    else {
        Serr();
    }
}