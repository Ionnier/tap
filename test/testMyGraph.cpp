#include "../unused/my_graph.cpp"
#include <fstream>

int main() {
    Graph g;
    ifstream f("./facebook/0.edges");

    int x, y;

    while (f >> x >> y)
    {
        g.addEdge(x, y);
    }

    g.dfs(cout, 236);
}