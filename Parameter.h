#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>
using namespace std;
class Parameter
{
private:
    string value;

public:
    Parameter(string value) : value(value) {}
    Parameter() {}
    // setters
    void setValue(const string &value)
    {
        Parameter::value = value;
    }
    string getValue()
    {
        return value;
    }

    // toString
    string toString()
    {
        return value;
    }
};
#endif