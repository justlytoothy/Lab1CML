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
    unsigned int currTokenIndex = 0;
    TokenType currTokenType() const
    {
        return currTokenIndex >= tokens.size() ? UNDEFINED : tokens.at(currTokenIndex).getType();
    }
    void advanceToken()
    {
        currTokenIndex++;
        // tokens.erase(tokens.begin());
    }
    void throwError()
    {
        throw currTokenIndex >= tokens.size() ? tokens.at(tokens.size() - 1) : tokens.at(currTokenIndex);
        // throw tokens.at(currTokenIndex);
    }
    string typeName(TokenType temp) const
    {
        switch (temp)
        {
        case COMMA:
            return "COMMA";
        case COLON:
            return "COLON";
        case COLON_DASH:
            return "COLON_DASH";
        case ID:
            return "ID";
        case PERIOD:
            return "PERIOD";
        case Q_MARK:
            return "Q_MARK";
        case LEFT_PAREN:
            return "LEFT_PAREN";
        case RIGHT_PAREN:
            return "RIGHT_PAREN";
        case MULTIPLY:
            return "MULTIPLY";
        case ADD:
            return "ADD";
        case SCHEMES:
            return "SCHEMES";
        case FACTS:
            return "FACTS";
        case RULES:
            return "RULES";
        case QUERIES:
            return "QUERIES";
        case STRING:
            return "STRING";
        case COMMENT:
            return "COMMENT";
        case EOFF:
            return "EOF";
        case UNDEFINED:
            return "UNDEFINED";
        default:
            return 0;
        }
    }
    void match(TokenType t)
    {
        // the cout should be removed for the final project output
        // cout << "token at index: " << currTokenIndex << " was type: " << typeName(currTokenType()) << " expected: " << typeName(t) << endl;

        if (currTokenType() == t)
        {
            advanceToken();
        }
        else
        {
            throwError();
        }
    }
    void run()
    {
        datalogProgram();
    }
    // maybe done
    void datalogProgram()
    {
        match(SCHEMES);
        match(COLON);
        scheme();
        schemeList();
        match(FACTS);
        match(COLON);
        factList();
        match(RULES);
        match(COLON);
        ruleList();
        match(QUERIES);
        match(COLON);
        query();
        queryList();
        match(EOFF);
    }
    // maybe done
    void schemeList()
    {
        if (currTokenType() == ID)
        {
            scheme();
            schemeList();
        }
        else
        {
        }
    }
    // maybe done
    void
    factList()
    {
        if (currTokenType() == ID)
        {
            fact();
            factList();
        }
        else
        {
        }
    }
    // maybe done
    void ruleList()
    {
        if (currTokenType() == ID)
        {
            rule();
            ruleList();
        }
        else
        {
        }
    }
    // maybe done
    void queryList()
    {
        if (currTokenType() == ID)
        {
            query();
            queryList();
        }
        else
        {
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
    // maybe done
    void fact()
    {
        match(ID);
        match(LEFT_PAREN);
        match(STRING);
        stringList();
        match(RIGHT_PAREN);
        match(PERIOD);
    }
    // maybe done
    void rule()
    {
        headPredicate();
        match(COLON_DASH);
        predicate();
        predicateList();
        match(PERIOD);
    }
    // maybe done
    void query()
    {
        predicate();
        match(Q_MARK);
    }
    // maybe done
    void headPredicate()
    {
        if (currTokenType() == ID)
        {

            match(ID);
            match(LEFT_PAREN);
            match(ID);
            idList();
            match(RIGHT_PAREN);
        }
        else
        {
        }
    }
    // maybe done
    void predicate()
    {
        if (currTokenType() == ID)
        {
            match(ID);
            match(LEFT_PAREN);
            parameter();
            parameterList();
            match(RIGHT_PAREN);
        }
        else
        {
        }
    }
    // maybe done
    void predicateList()
    {
        if (currTokenType() == COMMA)
        {
            match(COMMA);
            predicate();
            predicateList();
        }
        else
        {
        }
    }
    // maybe done
    void parameterList()
    {
        if (currTokenType() == COMMA)
        {
            match(COMMA);
            parameter();
            parameterList();
        }
        else
        {
        }
    }
    // maybe
    void stringList()
    {
        if (currTokenType() == COMMA)
        {
            match(COMMA);
            match(STRING);
            stringList();
        }
        else
        {
        }
    }
    void idList()
    {
        if (currTokenType() == COMMA)
        {
            match(COMMA);
            match(ID);
            idList();
        }
        else
        {
        }
    }
    // maybe done
    void parameter()
    {
        if (currTokenType() == STRING)
        {
            match(STRING);
        }
        else if (currTokenType() == ID)
        {
            match(ID);
        }
    }
};
#endif // LAB1_COMMAAUTOMATON_H
