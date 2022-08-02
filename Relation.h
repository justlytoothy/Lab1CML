#ifndef RELATION_H
#define RELATION_H
#include "Tuple.h"
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <map>
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
    bool addTupleCheck(Tuple t)
    {

        if (this->tuples.insert(t).second)
        {
            cout << "  " << t.toString(this->getHeader()) << endl;
            return true;
        }
        else
        {
            return false;
        }
    }
    set<Tuple> getTuples()
    {
        return tuples;
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

    Header combineHeaders(Header *h1, Header *h2, vector<unsigned int> uniqueCols)
    {
        Header combinedHeader;
        for (unsigned int i = 0; i < h1->size(); i++)
        {
            combinedHeader.push_back(h1->at(i));
        }
        for (unsigned int i : uniqueCols)
        {
            combinedHeader.push_back(h2->at(i));
        }
        return combinedHeader;
    }
    Relation *naturalJoin(Relation *other)
    {
        // give clearer names to the this and other relations
        Relation *r1 = this;
        Relation *r2 = other;

        Relation *output = new Relation();

        // set name of output relation
        output->setName(r1->getName() + " |x| " + r2->getName());

        map<unsigned int, unsigned int> overlap;
        vector<unsigned int> uniqueCols;
        Header headOne = r1->getHeader();
        Header headTwo = r2->getHeader();
        bool found = false;
        for (unsigned int i = 0; i < headTwo.size(); i++)
        {
            found = false;
            for (unsigned int j = 0; j < headOne.size(); j++)
            {
                if (headOne.at(j) == headTwo.at(i))
                {
                    found = true;
                    overlap.insert({j, i});
                }
            }
            if (!found)
            {
                uniqueCols.push_back(i);
            }
        }

        Header combinedHeader = this->combineHeaders(&headOne, &headTwo, uniqueCols);

        output->setHeader(combinedHeader);
        if (!overlap.empty())
        {
            for (Tuple t1 : r1->getTuples())
            {
                for (Tuple t2 : r2->getTuples())
                {
                    if (canJoin(&t1, &t2, overlap))
                    {
                        // cout << t1.toString(combinedHeader) << "::::::" << t2.toString(combinedHeader) << endl;
                        Tuple newTuple = combineTuple(&t1, &t2, uniqueCols);
                        output->addTuple(newTuple);
                    }
                }
            }
        }
        else
        {
            for (Tuple t1 : r1->getTuples())
            {
                for (Tuple t2 : r2->getTuples())
                {
                    Tuple newTuple = combineTuple(&t1, &t2, uniqueCols);
                    output->addTuple(newTuple);
                }
            }
        }
        return output;
    }
    bool canJoin(Tuple *t1, Tuple *t2, map<unsigned int, unsigned int> overlap)
    {
        map<unsigned int, unsigned int>::iterator it;

        for (it = overlap.begin(); it != overlap.end(); it++)
        {
            if (t1->at(it->first) != t2->at(it->second))
            {
                return false;
            }
        }
        return true;
    }

    Tuple combineTuple(Tuple *t1, Tuple *t2, vector<unsigned int> uniqueCols)
    {
        Tuple newTuple;
        for (unsigned int i = 0; i < t1->size(); i++)
        {
            newTuple.push_back(t1->at(i));
        }
        for (unsigned int i : uniqueCols)
        {
            newTuple.push_back(t2->at(i));
        }
        return newTuple;
    }
    string toString()
    {
        stringstream out;
        for (Tuple t : tuples)
        {
            if (t.size() > 0)
            {
                out << "  " << t.toString(header) << endl;
            }
        }
        return out.str();
    }
};
#endif