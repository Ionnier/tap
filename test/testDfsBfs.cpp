//
// Created by Dragos BAHRIM on 09.04.2024.
//

#include "graphs.hpp"
#include <fstream>

int main() {
    Graph g;
    ifstream f("./facebook/0.edges");

    int x, y;

    while (f >> x >> y)
    {
        g.add_node(x);
        g.add_node(y);
        g.add_edge(x, y);
    }

    for (auto &node : g.vertex_list())
    {
        if (node != 1)
        {
            continue;
        }
        g.dfs(&node);
        g.bfs(&node);
        break;
    }

}