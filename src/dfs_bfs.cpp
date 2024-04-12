//
// Created by Dragos BAHRIM on 09.04.2024.
//
#include <graphs.hpp>
#include <iostream>
using namespace std;

void Graph::dfs(Vertex *vertex)
{
    if (vertices.empty())
    {
        return;
    }

    auto v = Out.find(*vertex);

    if (v == Out.end())
    {
        return;
    }
    set<Vertex> visited;

    _dfs(vertex, visited);
}

void Graph::_dfs(Vertex *vertex, set<Vertex> &visited)
{
    if (vertices.empty())
    {
        return;
    }

    auto v = Out.find(*vertex);

    if (v == Out.end())
    {
        return;
    }

    auto discovered = visited.find(*vertex);

    if (discovered != visited.end())
    {
        return;
    }

    visited.insert(*vertex);

    cout << *vertex << " ";

    cin.get();

    for (auto &neighbor : (*v).second._list)
    {
        _dfs(&neighbor, visited);
    }
}

void Graph::bfs(Vertex *vertex)
{
    if (vertices.empty())
    {
        return;
    }

    auto v = Out.find(*vertex);

    if (v == Out.end())
    {
        return;
    }

    set<Vertex> visited;

    auto discovered = visited.find(*vertex);

    if (discovered != visited.end())
    {
        return;
    }

    queue<Vertex> to_visit;

    to_visit.push(*vertex);

    while (true)
    {
        if (to_visit.empty())
        {
            break;
        }
        auto s = to_visit.front();
        to_visit.pop();
        if (visited.find(s) != visited.end())
        {
            continue;
        }
        visited.insert(s);
        cout << s << " ";
        cin.get();
        auto d = Out.find(s);
        if (d == Out.end())
        {
            continue;
        }
        for (auto &neighbour : (*d).second._list)
        {
            to_visit.push(neighbour);
        }
    }
}
