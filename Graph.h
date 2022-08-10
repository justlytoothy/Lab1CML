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
    vector<int> postOrder;
    vector<set<int>> finalScc;
    stack<int> posts;
    set<int> marked;
    set<int> found;

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
    map<int, set<int>> getList()
    {
        return adjList;
    }
    vector<set<int>> getForest()
    {
        return finalScc;
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

    void dfs(int index)
    {
        marked.insert(index);
        posts.push(index);
        for (int i : reverseAdjList.at(index))
        {
            if (marked.find(i) == marked.end())
            {
                dfs(i);
            }
        }
        postOrder.push_back(posts.top());
        posts.pop();
    }
    void forwardDfs(int index)
    {
        marked.insert(index);
        found.insert(index);
        for (int p : adjList.at(index))
        {
            if (marked.find(p) == marked.end())
            {
                forwardDfs(p);
            }
        }
    }

    void dfsForestOrder()
    {
        for (unsigned int i = 0; i < nodes.size(); i++)
        {
            if (marked.find(i) == marked.end())
            {
                dfs(i);
            }
        }
        while (posts.size() > 0)
        {
            postOrder.push_back(posts.top());
            posts.pop();
        }

        reverse(postOrder.begin(), postOrder.end());
        marked.clear();
    }

    void dfsForest()
    {
        marked.clear();
        for (int i : postOrder)
        {
            if (marked.find(i) == marked.end())
            {
                forwardDfs(i);
                finalScc.push_back(found);
                found.clear();
            }
        }
        // for (vector<int> hi : finalScc)
        // {
        //     cout << "Tree: ";
        //     for (int i : hi)
        //     {
        //         cout << i << ", ";
        //     }
        //     cout << endl;
        // }
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