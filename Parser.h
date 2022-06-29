#ifndef LAB1_PARSER_H
#define LAB1_PARSER_H
#include <vector>
#include "Token.h"
#include <iostream>
class Parser
{
private:
    vector<Token> tokens;

public:
    Parser(const vector<Token> &tokens) : tokens(tokens) {}
    TokenType tokenType() const
    {
        return tokens.at(0).getType();
    }
    void advanceToken()
    {
        tokens.erase(tokens.begin());
    }
    void throwError()
    {
        throw tokens.at(0);
    }
    string match(TokenType t)
    {
        // the cout can be removed for the final project
        cout << "match: " << t << endl;
        string tokenValue = "DATA UNCAUGHT";
        if (tokenType() == t)
        {
            advanceToken();
        }
        else
        {
            throwError();
        }
        return tokenValue;
    }
    void idList()
    {
        if (tokenType() == COMMA)
        {
            match(COMMA);
            match(ID);
            idList();
        }
        else
        {
            cout << "hello" << endl;
        }
    }
};
#endif // LAB1_COMMAAUTOMATON_H
