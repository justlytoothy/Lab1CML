//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_RULESAUTOMATON_H
#define LAB1_RULESAUTOMATON_H
#include "Automaton.h"
class RulesAutomaton : public Automaton
{
private:
    void s0()
    {
        if (match('R'))
        {
            next();
            s1();
        }
        else
        {
            sError();
        } // this calls the error state
    }
    void s1()
    {
        if (match('u'))
        {
            next();
            s2(); // this represents accepting the input
        }
        else
        {
            sError();
        } // this calls the error state
    }
    void s2()
    {
        if (match('l'))
        {
            next();
            s3(); // this represents accepting the input
        }
        else
        {
            sError();
        } // this calls the error state
    }
    void s3()
    {
        if (match('e'))
        {
            next();
            s4(); // this represents accepting the input
        }
        else
        {
            sError();
        } // this calls the error state
    }
    void s4() {
        if (match('s')) {
            next();
            return; // this represents accepting the input
        } else {
            sError();
        } // this calls the error state
    }

public:
    RulesAutomaton()
    {
        type = TokenType::RULES; // set the type
    }
};
#endif // LAB1_RULESAUTOMATON_H
