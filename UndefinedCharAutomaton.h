//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_UNDEFINEDCHARAUTOMATON_H
#define LAB1_UNDEFINEDCHARAUTOMATON_H
#include "Automaton.h"
class UndefinedCharAutomaton : public Automaton
{
private:
    void s0()
    {
        if (!match(EOF))
        {
            next(); // read next character
            return; // accept the input
        }
        else
        {
            sError();
        }
    }

public:
    UndefinedCharAutomaton()
    {
        type = TokenType::UNDEFINED; // set the type
    }
};
#endif // LAB1_UNDEFINEDCHARAUTOMATON_H
