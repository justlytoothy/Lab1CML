//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_PERIODAUTOMATON_H
#define LAB1_PERIODAUTOMATON_H
#include "Automaton.h"
class PeriodAutomaton : public Automaton
{
private:
    void s0()
    {
        if (match('.'))
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
    PeriodAutomaton()
    {
        type = TokenType::PERIOD; // set the type
    }
};
#endif // LAB1_PERIODAUTOMATON_H
