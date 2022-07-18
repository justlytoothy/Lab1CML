#ifndef PREDICATE_H
#define PREDICATE_H
#include "Parameter.h"
#include <vector>
#include <sstream>
class Predicate
{
private:
    vector<Parameter> parameters;
    string name;

public:
    Predicate() {}
    // setters
    void setName(string newName)
    {
        name = newName;
    }
    void setParameters(vector<Parameter> newParameters)
    {
        parameters = newParameters;
    }

    // getters
    string getName()
    {
        return name;
    }
    vector<Parameter> getParameters()
    {
        return parameters;
    }
    vector<string> getAllValues()
    {
        vector<string> values;
        for (Parameter p : parameters)
        {
            values.push_back(p.getValue());
        }
        return values;
    }

    // adder
    void addParameter(Parameter parameter)
    {
        parameters.push_back(parameter);
    }

    // helper function
    void addParameter(string parameterValue)
    {
        Parameter parameter;
        parameter.setValue(parameterValue);
        parameters.push_back(parameter);
    }
    // toString
    string toString()
    {
        string sep = "";
        stringstream out;
        out << name << "(";
        for (Parameter currParam : parameters)
        {
            out << sep << currParam.toString();
            sep = ",";
        }
        out << ")";
        return out.str();
    }
};
#endif