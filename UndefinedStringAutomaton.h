//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_UNDEFINEDSTRINGAUTOMATON_H
#define LAB1_UNDEFINEDSTRINGAUTOMATON_H
#include "Automaton.h"
class UndefinedStringAutomaton : public Automaton
{
private:
    void s0()
    {
        if (!match(EOF) && match('\''))
        {
            next(); // read next character
            s1();   // accept the input
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
            if ((!match('\'')) && !peekEndOfFile())
            {
                next();
                s1();
            }
            else if (matchText("''"))
            {
                next();
                next();
                s1();
            }
            else if (peekEndOfFile())
            {
                return;
            }
            else
            {
                sError();
            }
        }
        else
        {
            return;
        }
    }

public:
    UndefinedStringAutomaton()
    {
        type = TokenType::UNDEFINED; // set the type
    }
};
#endif // LAB1_UNDEFINEDSTRINGAUTOMATON_H
