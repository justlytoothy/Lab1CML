//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_ENDOFFILEAUTOMATON_H
#define LAB1_ENDOFFILEAUTOMATON_H
#include "Automaton.h"
class EndOfFileAutomaton : public Automaton
{
private:
    void s0()
    {
        if (endOfFile())
        {
            next();
            cout << "EOF" << endl;
            return; // this represents accepting the input
        }
        else
        {
            sError();
        } // this calls the error state
    }

public:
    EndOfFileAutomaton()
    {
        type = TokenType::EOFF; // set the type
    }
};
#endif // LAB1_ENDOFFILEAUTOMATON_H
