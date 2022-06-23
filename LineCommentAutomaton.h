//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_LINECOMMENTAUTOMATON_H
#define LAB1_LINECOMMENTAUTOMATON_H
#include "Automaton.h"
class LineCommentAutomaton : public Automaton
{
    // Make terminate if reaches end of file with no closing tag
private:
    void s0()
    {
        if (match('#') && !peekEndOfFile())
        {
            if (!matchText("#|"))
            {
                next();
                s1();
            }
            else
            {
                sError();
            }
        }
        else
        {
            sError();
        } // this calls the error state
    }
    void s1()
    {
        if (!endOfFile())
        {
            if (match('\n'))
            {
                next();
                return;
            }
            else
            {
                next();
                s1();
            }
        }
        else
        {
            sError();
        }
    }

public:
    LineCommentAutomaton()
    {
        type = TokenType::COMMENT; // set the type
    }
};
#endif // LAB1_LINECOMMENTAUTOMATON_H
