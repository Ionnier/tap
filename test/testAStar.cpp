#include "graphs.hpp"
#include <iostream>
#include <a_star.h>

int main() {
    Graph g(true, true);
    g.add_node(1);
    g.add_node(2);
    g.add_node(3);
    g.add_node(4);
    g.add_node(5);
    g.add_node(6);
    g.add_node(7);
    g.add_edge(1, 2, 4);
    g.add_edge(1, 3, 3);
    g.add_edge(2, 6, 5);
    g.add_edge(2, 5, 12);
    g.add_edge(3, 5, 10);
    g.add_edge(3, 4, 6);
    g.add_edge(6, 7, 16);
    g.add_edge(5, 7, 5);

    cout << *Node::a_star(g, 1, {7}, [](int x){
        switch (x) {
            case 1: return 14;
            case 2: return 12;
            case 3: return 11;
            case 4: return 6;
            case 5: return 4;
            case 6: return 11;
            case 7: return 0;
            default: return 100;
        }
    });

}
