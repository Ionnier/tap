//
// Created by Dragos BAHRIM on 15.04.2024.
//
#include "graphs.hpp"
using namespace std;

#ifndef TAP_P_SEARCH_H
#define TAP_P_SEARCH_H
list<unsigned int> p_dfs(unsigned int,Graph&);
list<unsigned int> p_bfs(unsigned int,Graph&);
list<Vertex> p_frontier_bfs(Vertex s,const Graph& GG);
list<Vertex> p_dfs2(Vertex s,const Graph& GG);
list<Vertex> p_bfs2(Vertex s,const Graph& GG);
#endif //TAP_P_SEARCH_H
