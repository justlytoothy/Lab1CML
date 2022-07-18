#ifndef LAB1_PARSER_H
#define LAB1_PARSER_H
#include <vector>
#include "Token.h"
#include <iostream>
#include "Predicate.h"
#include "Rule.h"
#include "DatalogProgram.h"
#include "Parameter.h"
class Parser
{
private:
    vector<Token> tokens;
    DatalogProgram program;
    vector<Parameter> params;
    vector<Predicate> predicates;

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
    string getPrevTokenContents()
    {
        if (currTokenIndex < 0)
            throw "CUSTOM ERROR MESSAGE HERE";
        return tokens.at(currTokenIndex - 1).getContents();
    }

    string getCurrTokenContents()
    {
        if (currTokenIndex >= tokens.size())
            throw "CUSTOM ERROR MESSAGE HERE";
        return tokens.at(currTokenIndex).getContents();
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
    DatalogProgram run()
    {
        datalogProgram();
        return program;
    }

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

    void factList()
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

        Predicate newScheme;

        match(ID); // in our example this would be "snap"
        newScheme.setName(getPrevTokenContents());

        match(LEFT_PAREN);
        match(ID); // in our example this would be "s"

        Parameter firstParameter(false);
        firstParameter.setValue(getPrevTokenContents()); // make a new parameter

        newScheme.addParameter(firstParameter); // add our new parameter into our scheme

        idList(); // in our example this would be the list ["N", "a", "P"]
        for (Parameter id : params)
        {
            newScheme.addParameter(id);
        }
        params.clear();
        match(RIGHT_PAREN);

        program.addScheme(newScheme); // add scheme to our program
    }
    // not done
    void fact()
    {
        Predicate newFact;
        match(ID);
        newFact.setName(getPrevTokenContents());
        match(LEFT_PAREN);
        match(STRING);
        Parameter firstParam(true);
        firstParam.setValue(getPrevTokenContents());
        program.addDomain(firstParam.getValue());
        newFact.addParameter(firstParam);
        stringList();
        for (Parameter p : params)
        {
            newFact.addParameter(p);
            program.addDomain(p.getValue());
        }
        params.clear();
        match(RIGHT_PAREN);
        match(PERIOD);
        program.addFact(newFact);
    }

    void rule()
    {
        Rule newRule;
        Predicate newHead = headPredicate();
        newRule.setHead(newHead);
        match(COLON_DASH);
        Predicate firstBody = predicate();
        newRule.addBody(firstBody);
        predicateList();
        for (Predicate p : predicates)
        {
            newRule.addBody(p);
        }
        predicates.clear();
        match(PERIOD);
        program.addRule(newRule);
    }

    void query()
    {
        Predicate newQuery = predicate();
        match(Q_MARK);
        program.addQuery(newQuery);
    }

    Predicate headPredicate()
    {
        if (currTokenType() == ID)
        {
            Predicate newHead;

            match(ID); // in our example this would be "snap"
            newHead.setName(getPrevTokenContents());

            match(LEFT_PAREN);
            match(ID); // in our example this would be "s"

            Parameter firstParameter(false);
            firstParameter.setValue(getPrevTokenContents()); // make a new parameter

            newHead.addParameter(firstParameter); // add our new parameter into our Head

            idList(); // in our example this would be the list ["N", "a", "P"]
            for (Parameter id : params)
            {
                newHead.addParameter(id);
            }
            params.clear();
            match(RIGHT_PAREN);
            return newHead;

            // match(ID);
            // match(LEFT_PAREN);
            // match(ID);
            // idList();
            // match(RIGHT_PAREN);
        }
        else
        {
            Predicate newHead;
            return newHead;
        }
    }

    Predicate predicate()
    {
        if (currTokenType() == ID)
        {
            Predicate newPredicate;
            match(ID);
            newPredicate.setName(getPrevTokenContents());
            match(LEFT_PAREN);
            Parameter firstParam = parameter();
            newPredicate.addParameter(firstParam);
            parameterList();
            for (Parameter s : params)
            {
                newPredicate.addParameter(s);
            }
            params.clear();
            match(RIGHT_PAREN);
            return newPredicate;
        }
        else
        {
            Predicate newPredicate;
            return newPredicate;
        }
    }

    void predicateList()
    {
        if (currTokenType() == COMMA)
        {
            match(COMMA);
            Predicate temp = predicate();
            predicates.push_back(temp);
            predicateList();
        }
        else
        {
        }
    }

    void parameterList()
    {
        if (currTokenType() == COMMA)
        {
            match(COMMA);
            Parameter temp = parameter();
            params.push_back(temp);
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
            Parameter param(true);
            match(COMMA);
            match(STRING);
            param.setValue(getPrevTokenContents());
            params.push_back(param);
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
            Parameter param(false);
            match(COMMA);
            match(ID);
            param.setValue(getPrevTokenContents());
            params.push_back(param);
            idList();
        }
        else
        {
        }
    }

    Parameter parameter()
    {
        if (currTokenType() == STRING)
        {
            Parameter param(true);
            match(STRING);
            param.setValue(getPrevTokenContents());
            return param;
        }
        else if (currTokenType() == ID)
        {
            Parameter param(false);
            match(ID);
            param.setValue(getPrevTokenContents());
            return param;
        }
        else
        {
            Parameter param;
            return param;
        }
    }
};
#endif // LAB1_Parser_H
