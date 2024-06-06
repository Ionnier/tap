//
// Created by Dragos BAHRIM on 15.04.2024.
//
#include <p_search.h>
#include <stack>
#include <iostream>

list<unsigned int> p_dfs(unsigned int s, Graph &G) {
    list<unsigned int> output;
    unordered_set<unsigned int> visited;
    stack<unsigned int> p;
    p.push(s);

    while (!p.empty()) {

        unsigned int v = p.top();
        p.pop();

        if (visited.find(v) == visited.end()) {
            visited.insert(v);
            output.push_back(v);
            auto Nv = G.vector_neighbours(v);
#pragma omp parallel for
            for (int i = Nv.size() - 1; i >= 0; i--) {
#pragma omp critical
                {
                    G.remove_edge(v, Nv[i]);
                    G.remove_edge(Nv[i], i);
                    p.push(Nv[i]);
                }
            }
        }
    }

    return output;
}

list<unsigned int> p_bfs(unsigned int s, Graph &G) {
    list<unsigned int> output;
    unordered_set<unsigned int> visited;
    queue<unsigned int> q;

    visited.insert(s);
    q.push(s);

    while (!q.empty()) {

        unsigned int v = q.front();
        q.pop();
        output.push_back(v);

        for (unsigned int u: G.neighbours(v))
            if (visited.find(u) == visited.end()) {
                visited.insert(u);
                q.push(u);
                auto Nv = G.vector_neighbours(u);
#pragma omp parallel for
                for (int i = Nv.size() - 1; i >= 0; i--) {
#pragma omp critical
                    {
                        G.remove_edge(v, Nv[i]);
                        G.remove_edge(Nv[i], i);
                    }
                }
            }
    }

    return output;
}