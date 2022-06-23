//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_RIGHTPARENAUTOMATON_H
#define LAB1_RIGHTPARENAUTOMATON_H
#include "Automaton.h"
class RightParenAutomaton : public Automaton {
private:

    void s0() {
        if (match(')')) {
            next();
            return; // this represents accepting the input
        }
        else {
            sError();
        }// this calls the error state
    }
public:
    RightParenAutomaton() {
        type = TokenType::RIGHT_PAREN; // set the type
    }
};
#endif //LAB1_RIGHTPARENAUTOMATON_H
