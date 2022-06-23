//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_LEFTPARENAUTOMATON_H
#define LAB1_LEFTPARENAUTOMATON_H
#include "Automaton.h"
class LeftParenAutomaton : public Automaton
{
private:
    void s0()
    {
        if (match('('))
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
    LeftParenAutomaton()
    {
        type = TokenType::LEFT_PAREN; // set the type
    }
};
#endif // LAB1_LEFTPARENAUTOMATON_H
