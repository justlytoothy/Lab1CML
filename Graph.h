#ifndef GRAPH_H
#define GRAPH_H
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <stack>
using namespace std;

class Graph
{
    struct node
    {
        bool visited = false;
        int num;
        Rule rule;
        vector<node *> adj;
        vector<node *> revAdj;
    };

private:
    map<int, set<int>> adjList;
    map<int, set<int>> reverseAdjList;
    vector<node> nodes;
    vector<node *> visitOrder;

public:
    Graph() {}
    Graph(map<int, set<int>> adjList) : adjList(adjList) {}

    unsigned int size()
    {
        return adjList.size();
    }
    int getNodeIndex(int index)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            if (nodes.at(i).num == index)
            {
                return i;
            }
        }
        return -1;
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
        for (it = adjList.begin(); it != adjList.end(); it++)
        {
            for (int i : it->second)
            {
                nodes.at(getNodeIndex(it->first)).adj.push_back(&nodes.at(getNodeIndex(i)));
            }
        }
        for (it = reverseAdjList.begin(); it != reverseAdjList.end(); it++)
        {
            for (int i : it->second)
            {
                nodes.at(getNodeIndex(it->first)).revAdj.push_back(&nodes.at(getNodeIndex(i)));
            }
        }
        dfs(&nodes.at(0));
        for (node *n : visitOrder)
        {
            cout << n->num << " ";
        }
        cout << endl;
        // for (node n : nodes)
        // {
        //     cout << n.num << ": ";
        //     for (node *no : n.adj)
        //     {
        //         cout << no->num << ",";
        //     }
        //     cout << endl;
        // }
        // cout << "reverse:" << endl;
        // for (node n : nodes)
        // {
        //     cout << n.num << ": ";
        //     for (node *no : n.revAdj)
        //     {
        //         cout << no->num << ",";
        //     }
        //     cout << endl;
        // }
    }
    void dfs(node *n)
    {
        if (!n->visited)
        {
            n->visited = true;
            visitOrder.push_back(n);
            for (node *p : n->revAdj)
            {
                if (!p->visited)
                {
                    dfs(p);
                }
            }
        }
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