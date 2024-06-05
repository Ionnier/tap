//
// Created by Dragos BAHRIM on 01.06.2024.
//

#include "partition_refinement.h"
#include "graphs.hpp"

int main() {
    Graph g(true, true);
    g.add_node(1);
    g.add_node(2);
    g.add_node(3);
    g.add_node(4);
    g.add_node(5);
    g.add_node(6);
    g.add_edge(1, 2, 4);
    g.add_edge(1, 4, 3);
    g.add_edge(2, 3, 5);
    g.add_edge(2, 5, 12);
    g.add_edge(3, 6, 12);
    g.add_edge(4, 5, 12);
    g.add_edge(5, 6, 10);
    g.lexBfs();
}