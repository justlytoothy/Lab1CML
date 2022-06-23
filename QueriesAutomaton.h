//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_QUERIESAUTOMATON_H
#define LAB1_QUERIESAUTOMATON_H
#include "Automaton.h"
class QueriesAutomaton : public Automaton
{
    ///////Not Done!
private:
    void s0()
    {
        if (match('Q'))
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
        if (match('e'))
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
        if (match('r'))
        {
            next();
            s4(); // this represents accepting the input
        }
        else
        {
            sError();
        } // this calls the error state
    }
    void s4()
    {
        if (match('i'))
        {
            next();
            s5(); // this represents accepting the input
        }
        else
        {
            sError();
        } // this calls the error state
    }
    void s5()
    {
        if (match('e'))
        {
            next();
            s6(); // this represents accepting the input
        }
        else
        {
            sError();
        } // this calls the error state
    }
    void s6()
    {
        if (match('s'))
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
    QueriesAutomaton()
    {
        type = TokenType::QUERIES; // set the type
    }
};
#endif // LAB1_QUERIESAUTOMATON_H
