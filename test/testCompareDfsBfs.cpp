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
    Vertex vertex = 3490;
    list <Vertex> output;
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
    output = dfs(vertex, g);
    cout << "Millis dfs graph " << m.end() << " " << output.size() << endl;

    m.begin();
    output = bfs(vertex, g);
    cout << "Millis bfs graph" << m.end() << output.size() << endl;

    m.begin();
    output = p_dfs(vertex, g);
    cout << "Millis p_dfs graph" << m.end() << " " << output.size() << endl;

//    m.begin();
//    output = p_dfs2(vertex, g);
//    cout << "Millis p_dfs2 graph" << m.end() << " " << output.size() << endl;
//
//    m.begin();
//    p_bfs(vertex, g);
//    cout << "Millis p_bfs graph" << m.end() << endl;
//
//    m.begin();
//    output = p_bfs2(vertex, g);
//    cout << "Millis p_bfs2 graph" << m.end() << " " << output.size() << endl;
//
//    m.begin();
//    p_frontier_bfs(vertex, g);
//    cout << "Millis p_frontier_bfs graph" << m.end() << endl;


    // Bag PBFS
//    pbfs(g, vertex);


}