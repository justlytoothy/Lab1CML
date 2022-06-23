//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_ADDAUTOMATON_H
#define LAB1_ADDAUTOMATON_H
#include "Automaton.h"
class AddAutomaton : public Automaton
{
private:
    void s0()
    {
        if (match('+'))
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
    AddAutomaton()
    {
        type = TokenType::ADD; // set the type
    }
};
#endif // LAB1_ADDAUTOMATON_H
