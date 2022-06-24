//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_IDAUTOMATON_H
#define LAB1_IDAUTOMATON_H
#include "Automaton.h"
// need these for isalnum and isalpha
#include <stdio.h>
#include <ctype.h>
class IDAutomaton : public Automaton
{
private:
    void s0()
    {

        if (isalpha(curr()))
        {
            next();
            s1();
        }
        else
        {
            sError();
        }
    }
    void s1()
    {
        if (!endOfFile())
        {
            if (isalnum(curr()))
            {
                next();
                s1();
            }
            else
            {
                return; // accept
            }
        }
        else
        {
            return;
        }
    }

public:
    IDAutomaton()
    {
        type = TokenType::ID; // set the type
    }
};
#endif // LAB1_IDAUTOMATON_H
