//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_COLONAUTOMATON_H
#define LAB1_COLONAUTOMATON_H
#include "Automaton.h"
class ColonAutomaton : public Automaton {
private:
    void s0()
    {

        if (match(':'))
        {
            next();
            return; // this represents accepting the input
        }
        else
        {
            sError();
        } // this calls the error state
    }

public:
    ColonAutomaton() {
        type = TokenType::COLON; // set the type
    }
};
#endif //LAB1_COLONAUTOMATON_H
