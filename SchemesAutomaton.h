//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_SCHEMESAUTOMATON_H
#define LAB1_SCHEMESAUTOMATON_H
#include "Automaton.h"
class SchemesAutomaton : public Automaton
{
    ///////FINNISH
private:
    void s0()
    {
        if (match('S'))
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
        if (match('c'))
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
        if (match('h'))
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
    void s4()
    {
        if (match('m'))
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
    SchemesAutomaton()
    {
        type = TokenType::SCHEMES; // set the type
    }
};
#endif // LAB1_SCHEMESAUTOMATON_H
