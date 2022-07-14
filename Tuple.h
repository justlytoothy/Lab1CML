#ifndef TUPLE_H
#define TUPLE_H
#include "Header.h"
#include <set>
#include <sstream>
#include <string>
class Tuple
{

private:
    vector<string> values;

public:
    Tuple() {}
    Tuple(vector<string> values) : values(values) {}

    // You must define this to allow tuples to be put into a set
    bool operator<(const Tuple t) const
    {
        return values < t.values;
    }
    // Tuple :
    unsigned int size()
    {
        return values.size();
    }

    string at(unsigned int index)
    {
        if (index >= size())
        {
            throw "tuple at";
        }
        return values.at(index);
    }

    void push_back(string value)
    {
        values.push_back(value);
    }
    // This goes in your tuple class, note that tuple must include Header.h
    string toString(Header header)
    {
        stringstream out;
        string sep = "";
        if (size() != header.size())
        {
            cout << size() << " " << header.size() << endl;
            throw "Tuple to string";
        }
        for (unsigned i = 0; i < size(); i++)
        {
            string name = header.at(i);
            string value = at(i);
            out << sep << name << "=" << value;
            sep = ",";
        }
        return out.str();
    }

    // // Header :
    // unsigned int size()
    // {
    //     return attributes.size();
    // }

    // string at(unsigned int index)
    // {
    //     return attributes.at(index);
    // }

    // void push_back(string value)
    // {
    //     attributes.push_back(value);
    // }
    // TODO: add more delegation functions as needed
};
#endif