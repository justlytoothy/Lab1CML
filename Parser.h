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
    // string match(TokenType t)
    // {
    //     // the cout can be removed for the final project
    //     cout << "match: " << t << endl;
    //     string tokenValue = "DATA UNCAUGHT";
    //     if (tokenType() == t)
    //     {
    //         advanceToken();
    //     }
    //     else
    //     {
    //         throwError();
    //     }
    //     return tokenValue;
    // }
    void match(TokenType t)
    {
        // the cout should be removed for the final project output
        cout << "match: " << t << endl;

        if (tokenType() == t)
        {
            advanceToken();
        }
        else
        {
            throwError();
        }
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
            cout << "lambda" << endl;
        }
    }
    void scheme()
    {
        match(ID);
        match(LEFT_PAREN);
        match(ID);
        idList();
        match(RIGHT_PAREN);
    }
};
#endif // LAB1_COMMAAUTOMATON_H
