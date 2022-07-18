#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>
class Parameter
{
private:
    string value;
    bool isConstant;

public:
    Parameter(bool isConstant) : isConstant(isConstant) {}
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
    bool constant()
    {
        return isConstant;
    }

    // toString
    string toString()
    {
        return value;
    }
};
#endif