//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_UNDEFINEDCOMMENTAUTOMATON_H
#define LAB1_UNDEFINEDCOMMENTAUTOMATON_H
#include "Automaton.h"
class UndefinedCommentAutomaton : public Automaton
{
private:
    void s0()
    {
        if (!match(EOF) && matchText("#|"))
        {
            next();
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
            if (!matchText("|#") && !peekEndOfFile())
            {
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
    UndefinedCommentAutomaton()
    {
        type = TokenType::UNDEFINED; // set the type
    }
};
#endif // LAB1_UNDEFINEDCOMMENTAUTOMATON_H
