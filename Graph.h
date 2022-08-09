#ifndef GRAPH_H
#define GRAPH_H
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
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
    vector<vector<node *>> forest;
    vector<node *> postOrder;
    vector<vector<node *>> finalScc;

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
        dfsForestOrder();
        dfsForest();
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
    void forwardDfs(node *n)
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
        for (unsigned int i = 0; i < nodes.size(); i++)
        {
            if (!nodes.at(i).visited)
            {
                dfs(&nodes.at(i));
                forest.push_back(visitOrder);
                postOrder.push_back(visitOrder.at(visitOrder.size() - 1));

                visitOrder.pop_back();
            }
        }
        while (visitOrder.size() > 0)
        {
            postOrder.push_back(visitOrder.at(visitOrder.size() - 1));
            visitOrder.pop_back();
        }
        reverse(postOrder.begin(), postOrder.end());
        resetVisited();
    }
    void dfsForest()
    {
        for (unsigned int i = 0; i < nodes.size(); i++)
        {
            if (!nodes.at(i).visited)
            {
                dfs(&nodes.at(i));
                forest.push_back(visitOrder);
                postOrder.push_back(visitOrder.at(visitOrder.size() - 1));
                for (node *n : visitOrder)
                {
                    cout << n->num << " ";
                }
                cout << "::::before pop" << endl;
                visitOrder.pop_back();
            }
        }
        while (visitOrder.size() > 0)
        {
            postOrder.push_back(visitOrder.at(visitOrder.size() - 1));
            visitOrder.pop_back();
        }
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