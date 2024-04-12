#include <vector>
#include <map>
#include <string>
#include <iostream>

using namespace std;
class Graph
{
    unordered_map<int, vector<int>> nodes;
    unordered_map<string, int> edges;

    static string build_key(int &x, int &y)
    {
        return to_string(x) + " " + to_string(y);
    }

public:
    void addEdge(int x, int y)
    {
        if (nodes.find(x) != nodes.end())
        {
            bool found = false;
            for (auto &aux : nodes[x])
            {
                if (aux == y)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                nodes[x].push_back(y);
            }
        }
        else
        {
            nodes[x].push_back(y);
        }

        if (nodes.find(y) != nodes.end())
        {
            bool found = false;
            for (auto &aux : nodes[y])
            {
                if (aux == x)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                nodes[y].push_back(x);
            }
        }
        else
        {
            nodes[y].push_back(x);
        }

        string s = build_key(x, y), t = build_key(y, x);

        if (edges.find(s) == edges.end() && edges.find(t) == edges.end())
        {
            edges[s] = 0;
        }
    }

    int getNoVertices() const
    {
        return nodes.size();
    }

    int getNoEdges() const
    {
        return edges.size();
    }

    bool adjancy(int x, int y)
    {
        string s = build_key(x, y), t = build_key(y, x);

        if (edges.find(s) == edges.end() || edges.find(t) == edges.end())
        {
            return false;
        }
        return true;
    }

    unordered_map<string, int>::iterator iteratorEdges()
    {
        return edges.begin();
    }

    unordered_map<int, vector<int>>::iterator iterataorNodes()
    {
        return nodes.begin();
    }

    friend ostream &operator<<(ostream &out, const Graph &g)
    {
        for (auto &node : g.nodes)
        {
            out << node.first << " ";
            for (auto &adj : node.second)
            {
                out << adj << " ";
            }
            out << std::endl;
        }

        out << std::endl;

        for (auto &edge : g.edges)
        {
            out << edge.first << endl;
        }

        return out;
    }

    void dfs(ostream &out, int n)
    {
        if (nodes.find(n) == nodes.end())
        {
            return;
        }

        for (auto &node : nodes[n])
        {
            cout << node << " ";
            dfs(out, node);
        }
    }

    void removeEdge(int x, int y)
    {
        if (nodes.find(x) != nodes.end())
        {
            auto &aux = nodes[x];
            for (auto i = aux.begin(); i != aux.end(); i++)
            {
                if (*i == y)
                {
                    aux.erase(i);
                    break;
                }
            }
            if (aux.size() == 0)
            {
                nodes.erase(x);
            }
        }
        if (nodes.find(y) != nodes.end())
        {
            auto &aux = nodes[y];
            for (auto i = aux.begin(); i != aux.end(); i++)
            {
                if (*i == x)
                {
                    aux.erase(i);
                    break;
                }
            }
            if (aux.size() == 0)
            {
                nodes.erase(y);
            }
        }
        edges.erase(build_key(x, y));
        edges.erase(build_key(y, x));
    }
};
