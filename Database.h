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
    map<string, Relation*> relations;

public:
    Database() {}
    Database(map<string, Relation*> relations) : relations(relations) {}
};
#endif