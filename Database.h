#ifndef DATABASE_H
#define DATABASE_H
#include <set>
#include <sstream>
#include "Relation.h"
#include <string>
#include <vector>
#include <map>
using namespace std;
class Database
{
private:
    map<string, Relation *> relations;

public:
    Database() {}
    Database(map<string, Relation *> relations) : relations(relations) {}

    void addRelation(string name, Relation *relation)
    {
        relations.insert({name, relation});
    }
    void removeRelation(string name)
    {
        relations.erase(name);
    }
    void addTupleToRelation(string name, Tuple tuple)
    {
        Relation *relation = relations.at(name);
        relation->addTuple(tuple);
    }
    Relation *getRelation(string name)
    {
        return relations.at(name);
    }
    string toString()
    {
        stringstream out;
        map<string, Relation *>::iterator it;
        for (it = relations.begin(); it != relations.end(); it++)
        {
            out << "Name: " << it->first << endl;
            out << it->second->toString() << endl;
        }

        return out.str();
    }
};
#endif