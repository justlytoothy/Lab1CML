//
// Created by Jake Schilling on 6/21/22.
//

#ifndef LAB1_LEXER_H
#define LAB1_LEXER_H
#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include "Token.h"
#include "Automaton.h"
#include "IDAutomaton.h"
#include "ColonAutomaton.h"
#include "CommaAutomaton.h"
#include "ColonDashAutomaton.h"
#include "UndefinedCharAutomaton.h"
#include "EndOfFileAutomaton.h"
#include "PeriodAutomaton.h"
#include "BlockCommentAutomaton.h"
#include "LineCommentAutomaton.h"
#include "LeftParenAutomaton.h"
#include "RightParenAutomaton.h"
#include "QMarkAutomaton.h"
#include "FactsAutomaton.h"
#include "QueriesAutomaton.h"
#include "StringAutomaton.h"
#include "AddAutomaton.h"
#include "MultiplyAutomaton.h"
#include "SchemesAutomaton.h"
#include "RulesAutomaton.h"

class Lexer
{
private:
    vector<Automaton *> automata;
    vector<Token> tokens;

public:
    const vector<Token> &getTokens() const
    {
        return tokens;
    }
    void initializeAutomata()
    {
        automata.push_back(new EndOfFileAutomaton());
        automata.push_back(new BlockCommentAutomaton());
        automata.push_back(new LineCommentAutomaton());
        automata.push_back(new StringAutomaton());
        automata.push_back(new AddAutomaton());
        automata.push_back(new MultiplyAutomaton());
        automata.push_back(new LeftParenAutomaton());
        automata.push_back(new RightParenAutomaton());
        automata.push_back(new QMarkAutomaton());
        automata.push_back(new PeriodAutomaton());
        automata.push_back(new ColonAutomaton());
        automata.push_back(new ColonDashAutomaton());
        automata.push_back(new CommaAutomaton());
        automata.push_back(new FactsAutomaton());
        automata.push_back(new QueriesAutomaton());
        automata.push_back(new SchemesAutomaton());
        automata.push_back(new RulesAutomaton());
        automata.push_back(new IDAutomaton());
        automata.push_back(new UndefinedCharAutomaton());
    }
    vector<Token> run(string input)
    {
        this->initializeAutomata();
        unsigned int linesRead = 1;
        while (input.size() > 0)
        {
            while (isspace(input.at(0)))
            {
                if (input.at(0) == '\n')
                {
                    linesRead++;
                }
                input = input.substr(1);
            }
            Automaton *maxAutomaton = automata.at(0);

            unsigned int maxRead = 0;
            // Handle Whitespace later here

            for (unsigned int i = 0; i < automata.size(); i++)
            {
                Automaton *currentAutomaton = automata.at(i);
                if (currentAutomaton->run(input) > maxRead)
                {
                    maxRead = currentAutomaton->run(input);
                    maxAutomaton = currentAutomaton;
                }
            }

            Token currToken = Token(maxAutomaton->getType(), input.substr(0, maxRead), linesRead);
            linesRead += maxAutomaton->getNewLines();
            // cout << currToken.toString() << endl;
            input = input.substr(maxRead);
            tokens.push_back(currToken);
        }

        Token newToken = Token(automata.at(5)->getType(), "", linesRead + 1);
        tokens.push_back(newToken);
        return tokens;
    }
};
#endif // LAB1_LEXER_H
