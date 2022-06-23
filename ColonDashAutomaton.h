//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_COLONDASHAUTOMATON_H
#define LAB1_COLONDASHAUTOMATON_H
#include "Automaton.h"
class ColonDashAutomaton : public Automaton
{
private:
    void s0()
    {

        if (!peekEndOfFile() && match(':'))
        {
            next();
            s1();
        }
        else
            sError(); // this calls the error state
    }
    void s1()
    {
        if (match('-'))
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
    ColonDashAutomaton()
    {
        type = TokenType::COLON_DASH; // set the type
    }
};
#endif // LAB1_COLONDASHAUTOMATON_H
