#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "Relation.h"
#include "DatalogProgram.h"
#include "Database.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Header.h"
#include <set>
#include <vector>
class Interpreter
{
private:
    DatalogProgram program;
    Database database;
    set<Relation *> relations;
    vector<Relation *> queryOutputs;
    vector<Predicate> queries;
    vector<Rule> rules;

public:
    Interpreter(DatalogProgram program)
    {
        vector<Predicate> schemes = program.getSchemes();
        vector<Predicate> facts = program.getFacts();
        vector<Rule> rules = program.getRules();
        vector<Predicate> queries = program.getQueries();
        this->program = program;
        for (Predicate p : schemes)
        {
            Relation *schemeRel = new Relation();
            schemeRel->setName(p.getName());
            Header schemeHeader(p.getAllValues());
            schemeRel->setHeader(schemeHeader);
            database.addRelation(p.getName(), schemeRel);
            addRelation(schemeRel);
        }
        for (Predicate f : facts)
        {
            Tuple tuple(f.getAllValues());
            database.addTupleToRelation(f.getName(), tuple);
        }
    }
    Interpreter() {}
    ~Interpreter()
    {
        for (Relation *r : relations)
        {
            delete (r);
        }
    }
    Interpreter(set<Relation *> relations) : relations(relations) {}

    void addRelation(Relation *relation)
    {
        relations.insert(relation);
    }
    void evaluateRules()
    {
        cout << "in here" << endl;
        vector<Relation *> relations;

        for (Rule r : program.getRules())
        {
            bool first = true;

            rules.push_back(r);
            for (Predicate p : r.getBody())
            {
                if (first)
                {
                    Relation *first = evaluatePredicate(&p);
                    first = false;
                }
                else
                {
                }
                relations.push_back(evaluatePredicate(&p));
            }
        }
        cout << "we out" << endl;
    }

    void evaluateQueries()
    {
        for (Predicate q : program.getQueries())
        {
            queries.push_back(q);
            queryOutputs.push_back(evaluatePredicate(&q));
        }
    }
    Relation *evaluatePredicate(Predicate *predicate)
    {
        Relation *output = database.getRelation(predicate->getName());
        map<string, unsigned int> seen;
        unsigned int i = 0;
        vector<string> orderCheck;

        for (Parameter p : predicate->getParameters())
        {
            if (p.constant())
            {
                // select type 1 (int, value)
                output = output->select(i, p.getValue());
            }
            else
            {
                if (seenBefore(seen, p.getValue()))
                {
                    // (int, int)
                    output = output->select(seen.at(p.getValue()), i);
                }
                else
                {
                    orderCheck.push_back(p.getValue());
                    seen.insert({p.getValue(), i});
                    // mark it as seen
                }
            }
            i++;
        }
        vector<unsigned int> cols;
        for (string tmp : orderCheck)
        {
            cols.push_back(seen.at(tmp));
        }
        output = output->project(cols);
        // project
        output = output->rename(orderCheck);
        // rename

        return output;
    }
    bool seenBefore(map<string, unsigned int> seen, string name)
    {
        return seen.find(name) != seen.end();
    }
    string toString()
    {
        stringstream out;
        // out << database.toString() << endl;
        for (unsigned int i = 0; i < queryOutputs.size(); i++)
        {
            if (queryOutputs.at(i)->size() > 0)
            {
                out << queries.at(i).toString() << "? ";
                out << "Yes(" << queryOutputs.at(i)->size() << ")" << endl;
                out << queryOutputs.at(i)->toString();
            }
            else
            {
                out << queries.at(i).toString() << "? ";
                out << "No" << endl;
            }
        }
        return out.str();
    }
};
#endif