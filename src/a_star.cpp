#include "a_star.h"
bool Node::value_is_in(const vector<int> &destination) {
    return std::find_if(destination.begin(), destination.end(),[this](int x) {
        return x == this->myself;
    }) != destination.end();
}

bool Node::value_is_in(const vector<Node> &destination) {
    return std::find_if(destination.begin(), destination.end(),[this](const Node &x) {
        return x.myself == this->myself;
    }) != destination.end();
}

bool Node::value_is_in(const vector<Node*> &destination) {
    return std::find_if(destination.begin(), destination.end(),[this](const Node *x) {
        return x->myself == this->myself;
    }) != destination.end();
}

Node* Node::get_value_from(const vector<Node*> &destination) {
    return *(std::find_if(destination.begin(), destination.end(),[this](const Node *x) {
        return x->myself == this->myself;
    }));
}


Node::Node(int myself, Node* parent, double g): myself(myself), parent(parent), g(g) {

}


ostream& operator<<(ostream& out, const Node &aux) {
    out << "Node(value = " << aux.myself << ", g = " << aux.g;
    static int degree;
    if (aux.parent == nullptr) {
        degree = 0;
    }
    if (aux.parent != nullptr) {
        out << std::endl;
        for (int i = 0; i < degree; i++) {
            out << "  ";
        }
        out << "|-";

        degree += 1;

        out << "parent= " << " " << (*aux.parent);
    }

    if (aux.parent == nullptr) {
        degree = 0;
    }
    return out;
}

Node* Node::a_star(const Graph &graph, const int start, const vector<int> &destination, const function<double(unsigned int)> &h) {
    vector<Node*> close;
    vector<Node*> open;
    open.emplace_back(new Node(start, nullptr, 0));

    while (true) {
        if (open.empty()) {
            break;
        }

        std::sort(open.begin(), open.end(), [h](const Node *el1, const Node *el2) {
            return el1->g + h(el1->myself) > el2->g + h(el2->myself);
        });

        Node* current = open.back();
        open.pop_back();
        close.push_back(current);

        if (current->value_is_in(destination)) {
            return current;
        }

        for (auto &y: graph.neighbours(current->myself)) {
            auto s = Node(y, current, current-> g + graph.weight(current->myself, y));
            if (s.value_is_in(open)) {
                auto old_s = s.get_value_from(open);
                if (old_s->g > s.g) {
                    std::remove_if(open.begin(), open.end(),[old_s](Node * hey) {
                        return hey == old_s;
                    });
                    open.push_back(new Node(s));
                }
                continue;
            }

            if (s.value_is_in(close)) {
                auto old_s = s.get_value_from(close);
                if (old_s->g > s.g) {
                    std::remove_if(close.begin(), close.end(),[old_s](Node * hey) {
                        return hey == old_s;
                    });
                    close.push_back(new Node(s));
                }
                continue;
            }

            open.push_back(new Node(s));
        }

    }

    return nullptr;
}
