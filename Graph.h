#ifndef GRAPH_H
#define GRAPH_H
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <map>
using namespace std;

class Graph
{
    struct node
    {
        bool visited;
        int num;
        Rule rule;
    };

private:
    map<int, set<int>> adjList;
    map<int, set<int>> reverseAdjList;
    vector<node> nodes;

public:
    Graph() {}
    Graph(map<int, set<int>> adjList) : adjList(adjList) {}

    unsigned int size()
    {
        return adjList.size();
    }
    node getNode(int index)
    {
        for (node n : nodes)
        {
            if (n.num == index)
            {
                return n;
            }
        }
    }
    void addNode(int nodeNum, Rule point)
    {
        node nope;
        nope.num = nodeNum;
        nope.rule = point;
        nodes.push_back(nope);
    }
    void fillAdjacencyList()
    {
        for (node n : nodes)
        {
            set<int> adjacents;
            vector<Predicate> hey = n.rule.getBody();
            for (Predicate p : n.rule.getBody())
            {
                for (node no : nodes)
                {
                    Predicate head = no.rule.getHead();
                    if (head.getName() == p.getName())
                    {
                        adjacents.insert(no.num);
                    }
                }
            }
            adjList.insert({n.num, adjacents});
        }
        map<int, set<int>>::iterator it;
        for (it = adjList.begin(); it != adjList.end(); it++)
        {
            set<int> tmp;
            reverseAdjList.insert({it->first, tmp});
        }
        for (it = adjList.begin(); it != adjList.end(); it++)
        {
            for (int i : it->second)
            {
                reverseAdjList.at(i).insert(it->first);
            }
        }
    }
    void dfs(int index)
    {
        map<int, set<int>>::iterator it;
        vector<int> visitedOrder;
        vector<int> finalOrder;
        for (it = check.begin(); it != check.end(); it++)
        {

            cout << "dfs" << endl;
        }
        resetVisited();
    }
    void dfsTwo(node n) {

    }
    void dfsForestOrder()
    {
        cout << "dfs forest" << endl;
    }
    void dfsForest()
    {
        cout << "dfs forest" << endl;
    }
    void resetVisited()
    {
        for (node n : nodes)
        {
            n.visited = false;
        }
    }
    string toString()
    {
        stringstream out;
        string sep = "";
        map<int, set<int>>::iterator it;
        out << "Dependency Graph" << endl;
        for (it = adjList.begin(); it != adjList.end(); it++)
        {
            out << "R" << it->first << ":";
            sep = "";
            for (int i : it->second)
            {
                out << sep << "R" << i;
                sep = ",";
            }
            out << endl;
        }

        return out.str();
    }
};
#endif