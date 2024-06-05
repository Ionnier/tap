//
// Created by Dragos BAHRIM on 15.04.2024.
//
#include <p_search.h>
#include <stack>

list<unsigned int> p_dfs(unsigned int s,Graph& G){
    list<unsigned int> output;
    unordered_set<unsigned int> visited;
    stack<unsigned int> p;
    p.push(s);

    while(!p.empty()){

        unsigned int v = p.top();
        p.pop();

        if(visited.find(v) == visited.end()){
            visited.insert(v);
            output.push_back(v);
            auto Nv = G.vector_neighbours(v);
            for(auto u: Nv)
                p.push(u);
            G.isolate(v);
        }

    }

    return output;
}