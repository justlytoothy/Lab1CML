#ifndef RELATION_H
#define RELATION_H
#include "Tuple.h"
#include <set>
#include <sstream>
#include <string>
#include <vector>
class Relation
{
private:
    string name;
    Header header;
    set<Tuple> tuples;

public:
    Relation() {}
    ~Relation() {}

    void setName(string newName)
    {
        name = newName;
    }
    void setHeader(Header newHeader)
    {
        header = newHeader;
    }
    void addTuple(Tuple t)
    {
        tuples.insert(t);
    }
    string getName()
    {
        return name;
    }
    Header getHeader()
    {
        return header;
    }
    unsigned int size()
    {
        return tuples.size();
    }
    Relation *select(unsigned int col, string value)
    {
        Relation *output = new Relation(); // make a new empty relation

        output->setName(this->name);     // copy over name
        output->setHeader(this->header); // copy over header

        for (Tuple currTuple : this->tuples)
        { // loop through each tuple
            if (currTuple.at(col) == value)
            {
                output->addTuple(currTuple);
            }
        }

        return output;
    }

    Relation *select(unsigned int col1, unsigned int col2)
    {
        Relation *output = new Relation();
        // check to make sure both columns are in bounds
        if (col1 >= this->header.size() || col2 >= this->header.size())
        {
            cout << this->header.size() << " " << col1 << " " << col2 << endl;
            throw "Select 2 col error";
        }
        else
        {
            output->setName(this->name);
            output->setHeader(this->header);
            for (Tuple currTuple : this->tuples)
            { // loop through each tuple
                if (currTuple.at(col1) == currTuple.at(col2))
                {
                    output->addTuple(currTuple);
                }
            }
        }
        // write your code here
        return output;
    }
    Relation *rename(vector<string> newAttributes)
    {
        // Make a new empty relation
        Relation *output = new Relation();
        // Make a new Header with newAttributes as its contents
        Header newHeader(newAttributes);
        output->setName(this->name);
        output->setHeader(newHeader);
        for (Tuple t : this->tuples)
        {
            output->addTuple(t);
        }
        // copy over the old name
        // copy over all of the existing tuples
        return output;
    }
    Relation *project(vector<unsigned int> indiciesToKeep)
    {
        // Make a new empty relation
        Relation *output = new Relation();
        output->setName(this->name);
        // copy over the old name
        Header newHeader;
        for (unsigned int i : indiciesToKeep)
        {
            newHeader.push_back(this->header.at(i));
        }
        output->setHeader(newHeader);
        for (Tuple t : this->tuples)
        {
            Tuple newTuple;
            for (unsigned int i : indiciesToKeep)
            {
                newTuple.push_back(t.at(i));
            }
            output->addTuple(newTuple);
        }

        return output;
    }
    string toString()
    {
        stringstream out;
        for (Tuple t : tuples)
        {
            if (t.size() > 0)
            {
                out << t.toString(header) << endl;
            }
        }
        return out.str();
    }
};
#endif