//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_COMMAAUTOMATON_H
#define LAB1_COMMAAUTOMATON_H
#include "Automaton.h"
class CommaAutomaton : public Automaton {
private:

    void s0() {
        if (match(',')) {
            next();
            return; // this represents accepting the input
        }
        else {
            sError();
        }// this calls the error state
    }
public:
    CommaAutomaton() {
        type = TokenType::COMMA; // set the type
    }
};
#endif //LAB1_COMMAAUTOMATON_H
