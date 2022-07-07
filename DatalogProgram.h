#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H
#include "Predicate.h"
#include "Rule.h"
#include <set>
#include <sstream>
#include <string>
class DatalogProgram
{
private:
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Rule> rules;
    vector<Predicate> queries;
    set<string> domain;

public:
    DatalogProgram() {}
    // setters
    void setSchemes(vector<Predicate> newSchemes)
    {
        schemes = newSchemes;
    }
    void setFacts(vector<Predicate> newFacts)
    {
        facts = newFacts;
    }
    void setRules(vector<Rule> newRules)
    {
        rules = newRules;
    }
    void setQueries(vector<Predicate> newQueries)
    {
        queries = newQueries;
    }
    void setDomain(set<string> newDomain)
    {
        domain = newDomain;
    }

    // getters
    vector<Predicate> getSchemes()
    {
        return schemes;
    }
    vector<Predicate> getFacts()
    {
        return facts;
    }
    vector<Rule> getRules()
    {
        return rules;
    }
    vector<Predicate> getQueries()
    {
        return queries;
    }
    set<string> getDomain()
    {
        return domain;
    }

    // adder
    void addScheme(Predicate newScheme)
    {
        schemes.push_back(newScheme);
    }
    void addFact(Predicate newFact)
    {
        facts.push_back(newFact);
    }
    void addRule(Rule newRule)
    {
        rules.push_back(newRule);
    }
    void addQuery(Predicate newQuery)
    {
        queries.push_back(newQuery);
    }
    void addDomain(string newDomain)
    {
        domain.insert(newDomain);
    }

    // toString
    string toString()
    {
        stringstream out;
        out << "Schemes(" << schemes.size() << "):" << endl;
        for (Predicate scheme : schemes)
        {
            out << "  " << scheme.toString() << endl;
        }
        out << "Facts(" << facts.size() << "):" << endl;
        for (Predicate fact : facts)
        {
            out << "  " << fact.toString() << "." << endl;
        }
        out << "Rules(" << rules.size() << "):" << endl;
        for (Rule rule : rules)
        {
            out << "  " << rule.toString() << "." << endl;
        }
        out << "Queries(" << queries.size() << "):" << endl;
        for (Predicate query : queries)
        {
            out << "  " << query.toString() << "?" << endl;
        }
        out << "Domain(" << domain.size() << "):" << endl;
        for (string temp : domain)
        {
            out << "  " << temp << endl;
        }
        return out.str();
    }
};
#endif