#ifndef RULE_H
#define RULE_H
#include "Predicate.h"
#include <vector>
#include <sstream>

class Rule
{
private:
    Predicate head;
    vector<Predicate> body;

public:
    Rule() {}
    // setters
    void setHead(Predicate newHead)
    {
        head = newHead;
    }
    void setBody(vector<Predicate> newBody)
    {
        body = newBody;
    }

    // getters
    Predicate getHead()
    {
        return head;
    }
    vector<Predicate> getBody()
    {
        return body;
    }

    // adder
    void addBody(Predicate predicate)
    {
        body.push_back(predicate);
    }

    // toString
    string toString()
    {
        stringstream out;
        string sep = "";
        out << head.toString() << " :- ";
        for (Predicate predicate : body)
        {
            out << sep << predicate.toString();
            sep = ",";
        }
        out << ".";
        return out.str();
    }
};
#endif