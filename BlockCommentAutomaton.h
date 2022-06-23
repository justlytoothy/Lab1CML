//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_BLOCKCOMMENTAUTOMATON_H
#define LAB1_BLOCKCOMMENTAUTOMATON_H
#include "Automaton.h"
class BlockCommentAutomaton : public Automaton
{
    //Make terminate if reaches end of file with no closing tag
private:
    void s0()
    {
        if (matchText("#|")) {
            next();
            next();
            s1();
        }
        else {
            sError();
        }
    }
    void s1()
    {
        if (!endOfFile()) {
            if (matchText("|#")) {
                next();
                next();
                return;
            }
            else {
                next();
                s1();
            }
        }
        else {
            sError();
        }
    }


public:
    BlockCommentAutomaton()
    {
        type = TokenType::COMMENT; // set the type
    }
};
#endif // LAB1_BLOCKCOMMENTAUTOMATON_H
