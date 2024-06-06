#ifndef TAP_A_STAR_H
#define TAP_A_STAR_H
#include <vector>
#include <graphs.hpp>
#include <iostream>
#include <functional>

using namespace std;
struct Node {
    int myself;
    Node* parent;
    double g;

    bool value_is_in(const vector<int> &destination);

    bool removeMyselfFrom(priority_queue<Node*, vector<Node*>, function<bool(const Node*, const Node*) > > &destination);

    bool value_is_in(const vector<Node> &destination);

    bool value_is_in(const vector<Node*> &destination);

    Node* get_value_from(const vector<Node*> &destination);

    Node(int myself, Node* parent = nullptr, double g =0);

    friend ostream& operator<<(ostream& out, const Node &aux);

    static Node* a_star(const Graph &graph, const int start, const vector<int> &destination, const function<double(unsigned int)> &h);

    Node *value_is_in(
            const priority_queue<Node *, vector<Node *>, function<bool(const Node *,
                                                                             const Node *)>> &destination);
};
#endif //TAP_A_STAR_H
