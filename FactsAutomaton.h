//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_FACTSAUTOMATON_H
#define LAB1_FACTSAUTOMATON_H
#include "Automaton.h"
class FactsAutomaton : public Automaton
{
    ///////FINISH
private:
    void s0()
    {
        if (matchText("Facts"))
        {
            next();
            next();
            next();
            next();
            next();
            return;
        }
        else
        {
            sError();
        } // this calls the error state
    }


public:
    FactsAutomaton()
    {
        type = TokenType::FACTS; // set the type
    }
};
#endif // LAB1_FACTSAUTOMATON_H
