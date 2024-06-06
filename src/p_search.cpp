//
// Created by Dragos BAHRIM on 15.04.2024.
//
#include <p_search.h>
#include <stack>
#include <iostream>

void isolate(Vertex v, Graph& G){
    Graph::AdjList& Nv = G.In[v];
#pragma omp parallel for
    for(auto i = 0; i < Nv._map.bucket_count(); i++){
        for(auto it = Nv._map.begin(i); it != Nv._map.end(i); it++){
            G.erase(G.Out[it->first],v);
        }
    }
}

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
                    G.remove_edge(Nv[i], v);
                }
            }
        }
    }

    return output;
}

list<Vertex> p_dfs2(Vertex s,const Graph& GG){
    Graph G = GG;
    list<unsigned int> output;
    unordered_set<unsigned int> visited;
    stack<unsigned int> p;

    p.push(s);

    while(!p.empty()){

        unsigned int v = p.top();
        p.pop();


        if(visited.find(v) == visited.end()){
            visited.insert(v);
            isolate(v, G);
            output.push_back(v);
            list<unsigned int> Nv = G.neighbours(v);
            Nv.reverse();
            for(unsigned int u : Nv)
                p.push(u);
        }

    }

    return output;
}

list<unsigned int> p_bfs(unsigned int s, Graph &GG) {
    auto G = GG;
    list<unsigned int> output;
    unordered_set<unsigned int> visited;
    queue<unsigned int> q;

    visited.insert(s);
    q.push(s);

    while (!q.empty()) {

        unsigned int v = q.front();
        q.pop();
        output.push_back(v);
        for (Vertex u: G.neighbours(v)) {
            if (visited.find(u) != visited.end()) {
                visited.insert(u);
                auto Nv = G.vector_neighbours(u);
#pragma omp parallel for
                for (int i = Nv.size() - 1; i >= 0; i--) {
#pragma omp critical
                    {
                        q.push(u);
                        G.remove_edge(v, Nv[i]);
                        G.remove_edge(Nv[i], i);
                    }
                }
            }
        }
    }

    return output;
}

list<Vertex> p_frontier_bfs(Vertex s,const Graph& GG){
    auto G = GG;
    list<Vertex> output;
    unordered_set<Vertex> visited;
    vector<Vertex> frontier;
    list<Vertex> external_frontier;

    visited.insert(s);
    frontier.push_back(s);

    while (!frontier.empty()) {
#pragma omp parallel for
        for (auto &i: frontier) {
            output.push_back(i);
            for (auto &v: G.vector_neighbours(i)) {
                if (visited.find(v) == visited.end()) {
                    visited.insert(v);
                    external_frontier.push_back(v);

                    auto Nv = G.vector_neighbours(v);
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
        }
        frontier.clear();
        for (auto &i: external_frontier) {
            frontier.push_back(i);
        }
        external_frontier.clear();
    }

    return output;
}

list<Vertex> p_bfs2(Vertex s, const Graph &GG) {
    auto G = GG;
    list<unsigned int> output;
    unordered_set<unsigned int> visited;
    queue<unsigned int> q;

    visited.insert(s);
    q.push(s);
    isolate(s, G);

    while(!q.empty()){

        unsigned int v = q.front();
        q.pop();
        output.push_back(v);

        for(unsigned int u : G.neighbours(v))
            if(visited.find(u) == visited.end()){
                visited.insert(u);
                q.push(u);
                isolate(u, G);
            }
    }

    return output;

}
