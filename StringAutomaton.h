//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_STRINGAUTOMATON_H
#define LAB1_STRINGAUTOMATON_H
#include "Automaton.h"
///Check for unterminated string before end of file, check later for back to back quotes
class StringAutomaton : public Automaton
{
private:
    void s0()
    {
        if (match('\'') && !peekEndOfFile())
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
        if (!endOfFile()) {
            if (matchText("\'\'")) {
                next();
                next();
                s1();
            }
            else {
                if (match('\'')) {
                    next();
                    return;
                }
                else {
                    next();
                    s1();
                }

            }
        }
        else {
            sError();
        }
    }


public:
    StringAutomaton()
    {
        type = TokenType::STRING; // set the type
    }
};
#endif // LAB1_STRINGAUTOMATON_H

/*
     void s1()
    {
        if (!endOfFile()) {
            if (!match('\'')) {
                next();
                s1();
            } else {
                next();
                if (matchNext('\'')) {
                    next();
                    s1();
                } else {
                    return;
                }
            }
        }
        else {
            sError();
        }
    }
 */
