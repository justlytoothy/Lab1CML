#ifndef HEADER_H
#define HEADER_H
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
class Header
{
private:
    vector<string> attributes;

public:
    Header() {}
    Header(vector<string> attributes) : attributes(attributes) {}

    unsigned int size()
    {
        return attributes.size();
    }

    string at(unsigned int index)
    {
        if (index >= size())
        {
            throw "header at";
        }
        return attributes.at(index);
    }

    void push_back(string value)
    {
        attributes.push_back(value);
    }
};
#endif