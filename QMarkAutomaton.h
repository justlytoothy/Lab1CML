//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_QMARKAUTOMATON_H
#define LAB1_QMARKAUTOMATON_H
#include "Automaton.h"
class QMarkAutomaton : public Automaton
{
private:
    void s0()
    {
        if (match('?'))
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
    QMarkAutomaton()
    {
        type = TokenType::Q_MARK; // set the type
    }
};
#endif // LAB1_QMARKAUTOMATON_H
