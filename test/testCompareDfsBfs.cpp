//
// Created by Dragos BAHRIM on 12.04.2024.
//

#include <omp.h>
#include <iostream>
#include <graphs.hpp>
#include <fstream>
#include "TimeMeasurementUtil.h"
#include <search.hpp>
#include <p_search.h>

using namespace std;

int main() {
    Graph g;
    ifstream f("../facebook/facebook_combined.txt");
    TimeMeasurementUtil m;
    int x, y;
    m.begin();
    while (f >> x >> y)
    {
        g.add_node(x);
        g.add_node(y);
        g.add_edge(x, y);
    }
    cout << "Millis read graph" << m.end() << endl;

    m.begin();
    dfs(4004, g);
    cout << "Millis dfs graph" << m.end() << endl;
//
//    m.begin();
//    bfs(4004, g);
//    cout << "Millis bfs graph" << m.end() << endl;
//
    m.begin();
    p_dfs(3980, g);
    cout << "Millis p_dfs graph" << m.end() << endl;

    // Bag PBFS
//    pbfs(g, 4004);


}