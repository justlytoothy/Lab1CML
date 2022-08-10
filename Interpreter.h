#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "Relation.h"
#include "DatalogProgram.h"
#include "Database.h"
#include "Predicate.h"
#include "Parameter.h"
#include "Header.h"
#include "Graph.h"
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
            Relation *r = database.getRelation(f.getName());
            r->addTuple(tuple);
            // database.addTupleToRelation(f.getName(), tuple);
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
    // void evaluateRules()
    // {

    //     Graph graph;
    //     unsigned int nodeNum = 0;
    //     for (Rule r : program.getRules())
    //     {
    //         graph.addNode(nodeNum, r);
    //         nodeNum++;
    //     }
    //     graph.fillAdjacencyList();
    //     cout << graph.toString() << endl
    //          << endl;
    //     cout << "Rule Evaluation" << endl;
    //     unsigned int numPasses = 0;
    //     bool somethingChanged = true;
    //     while (somethingChanged)
    //     {
    //         somethingChanged = false;
    //         numPasses++;
    //         for (Rule r : program.getRules())
    //         {
    //             cout << r.toString() << endl;
    //             Predicate head = r.getHead();
    //             vector<string> headCols = head.getAllValues();
    //             bool isFirst = true;
    //             Relation *first;
    //             rules.push_back(r);
    //             for (Predicate p : r.getBody())
    //             {
    //                 if (isFirst)
    //                 {
    //                     first = evaluatePredicate(&p);
    //                     isFirst = false;
    //                 }
    //                 else
    //                 {
    //                     Relation *tmp = evaluatePredicate(&p);
    //                     first = first->naturalJoin(tmp);
    //                 }
    //             }
    //             Header header = first->getHeader();
    //             vector<unsigned int> indices;
    //             for (string s : headCols)
    //             {
    //                 for (unsigned int i = 0; i < header.size(); i++)
    //                 {
    //                     if (header.at(i) == s)
    //                     {
    //                         indices.push_back(i);
    //                     }
    //                 }
    //             }

    //             first = first->project(indices);
    //             Relation *original = database.getRelation(head.getName());
    //             vector<string> newNames;
    //             for (unsigned int i = 0; i < original->getHeader().size(); i++)
    //             {
    //                 newNames.push_back(original->getHeader().at(i));
    //             }
    //             first = first->rename(newNames);
    //             for (Tuple t : first->getTuples())
    //             {
    //                 bool checkIt = database.addTupleToRelation(head.getName(), t);
    //                 if (checkIt)
    //                 {
    //                     somethingChanged = true;
    //                 }
    //             }
    //         }
    //     }
    //     cout << endl
    //          << "Schemes populated after " << numPasses << " passes through the Rules."
    //          << endl
    //          << endl;
    // }

    void evaluateRules()
    {
        Graph graph;
        unsigned int nodeNum = 0;
        for (Rule r : program.getRules())
        {
            graph.addNode(nodeNum, r);
            nodeNum++;
        }
        graph.fillAdjacencyList();
        vector<set<int>> rulesScc = graph.getForest();
        cout << graph.toString() << endl;
        rules = program.getRules();
        vector<set<int>> scc = graph.getForest();
        map<int, set<int>> adjList = graph.getList();
        cout << "Rule Evaluation" << endl;
        for (set<int> v : scc)
        {
            if (v.size() > 1)
            {
                cout << "SCC: ";
                string sep = "";
                vector<Rule> checkRules;
                for (int i : v)
                {
                    checkRules.push_back(rules.at(i));
                    cout << sep << "R" << i;
                    sep = ",";
                }
                cout << endl;
                int numPasses = 0;
                bool somethingChanged = true;
                while (somethingChanged)
                {
                    somethingChanged = false;
                    numPasses++;
                    for (Rule r : checkRules)
                    {
                        cout << r.toString() << endl;
                        Predicate head = r.getHead();
                        vector<string> headCols = head.getAllValues();
                        bool isFirst = true;
                        Relation *first;
                        rules.push_back(r);
                        for (Predicate p : r.getBody())
                        {
                            if (isFirst)
                            {
                                first = evaluatePredicate(&p);
                                isFirst = false;
                            }
                            else
                            {
                                Relation *tmp = evaluatePredicate(&p);
                                first = first->naturalJoin(tmp);
                            }
                        }
                        Header header = first->getHeader();
                        vector<unsigned int> indices;
                        for (string s : headCols)
                        {
                            for (unsigned int i = 0; i < header.size(); i++)
                            {
                                if (header.at(i) == s)
                                {
                                    indices.push_back(i);
                                }
                            }
                        }

                        first = first->project(indices);
                        Relation *original = database.getRelation(head.getName());
                        vector<string> newNames;
                        for (unsigned int i = 0; i < original->getHeader().size(); i++)
                        {
                            newNames.push_back(original->getHeader().at(i));
                        }
                        first = first->rename(newNames);
                        for (Tuple t : first->getTuples())
                        {
                            bool checkIt = database.addTupleToRelation(head.getName(), t);
                            if (checkIt)
                            {
                                somethingChanged = true;
                            }
                        }
                    }
                }
                cout << numPasses << " passes: ";
                sep = "";
                for (int i : v)
                {
                    cout << sep << "R" << i;
                    sep = ",";
                }
                cout << endl;
            }
            else if (!graph.hasSelf(v))
            { // trivial only go once

                for (int i : v)
                {

                    cout << "SCC: R" << i << endl;
                    Rule r = rules.at(i);
                    cout << r.toString() << endl;
                    Predicate head = r.getHead();
                    vector<string> headCols = head.getAllValues();
                    bool isFirst = true;
                    Relation *first;
                    rules.push_back(r);
                    for (Predicate p : r.getBody())
                    {
                        if (isFirst)
                        {
                            first = evaluatePredicate(&p);
                            isFirst = false;
                        }
                        else
                        {
                            Relation *tmp = evaluatePredicate(&p);
                            first = first->naturalJoin(tmp);
                        }
                    }
                    Header header = first->getHeader();
                    vector<unsigned int> indices;
                    for (string s : headCols)
                    {
                        for (unsigned int i = 0; i < header.size(); i++)
                        {
                            if (header.at(i) == s)
                            {
                                indices.push_back(i);
                            }
                        }
                    }

                    first = first->project(indices);
                    Relation *original = database.getRelation(head.getName());
                    vector<string> newNames;
                    for (unsigned int i = 0; i < original->getHeader().size(); i++)
                    {
                        newNames.push_back(original->getHeader().at(i));
                    }
                    first = first->rename(newNames);
                    for (Tuple t : first->getTuples())
                    {
                        database.addTupleToRelation(head.getName(), t);
                    }

                    cout << "1 passes: R" << i << endl;
                }
            }
            else if (graph.hasSelf(v))
            {
                int numPasses = 0;
                bool somethingChanged = true;
                for (int i : v)
                {
                    cout << "SCC: R" << i << endl;
                    while (somethingChanged)
                    {
                        somethingChanged = false;
                        numPasses++;
                        Rule r = rules.at(i);
                        cout << r.toString() << endl;
                        Predicate head = r.getHead();
                        vector<string> headCols = head.getAllValues();
                        bool isFirst = true;
                        Relation *first;
                        rules.push_back(r);
                        for (Predicate p : r.getBody())
                        {
                            if (isFirst)
                            {
                                first = evaluatePredicate(&p);
                                isFirst = false;
                            }
                            else
                            {
                                Relation *tmp = evaluatePredicate(&p);
                                first = first->naturalJoin(tmp);
                            }
                        }
                        Header header = first->getHeader();
                        vector<unsigned int> indices;
                        for (string s : headCols)
                        {
                            for (unsigned int i = 0; i < header.size(); i++)
                            {
                                if (header.at(i) == s)
                                {
                                    indices.push_back(i);
                                }
                            }
                        }

                        first = first->project(indices);
                        Relation *original = database.getRelation(head.getName());
                        vector<string> newNames;
                        for (unsigned int i = 0; i < original->getHeader().size(); i++)
                        {
                            newNames.push_back(original->getHeader().at(i));
                        }
                        first = first->rename(newNames);
                        for (Tuple t : first->getTuples())
                        {
                            bool checkIt = database.addTupleToRelation(head.getName(), t);
                            if (checkIt)
                            {
                                somethingChanged = true;
                            }
                        }
                    }
                    cout << numPasses << " passes: R" << i << endl;
                }
            }
        }
    }

    void evaluateQueries()
    {
        cout << endl
             << "Query Evaluation" << endl;
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
