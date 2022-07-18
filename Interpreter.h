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
    void evaluateQueries()
    {
        for (Predicate q : program.getQueries())
        {
            queryOutputs.push_back(evaluatePredicate(q));
        }
    }
    Relation *evaluatePredicate(Predicate predicate)
    {
        Relation *output = database.getRelation(predicate.getName());
        map<string, unsigned int> seen;
        unsigned int i = 0;
        for (Parameter p : predicate.getParameters())
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
                    seen.insert({p.getValue(), i});
                    // mark it as seen
                }
            }
            i++;
        }
        // project
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
        for (Relation *r : queryOutputs)
        {
            out << r->toString() << endl;
        }
        return out.str();
    }
};
#endif