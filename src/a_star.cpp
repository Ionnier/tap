#include "a_star.h"
#include <functional>
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

    auto asd = [h](const Node *el1, const Node *el2) {
        return el1->g + h(el1->myself) > el2->g + h(el2->myself);
    };
    const function<bool(const Node*, const Node*)> bsd = asd;
    priority_queue<Node *, vector<Node *>, function<bool(const Node *, const Node *)>> open(asd);

    open.push(new Node(start, nullptr, 0));

    while (true) {
        if (open.empty()) {
            break;
        }

        Node* current = open.top();
        open.pop();
        close.push_back(current);

        if (current->value_is_in(destination)) {
            return current;
        }

        for (auto &y: graph.neighbours(current->myself)) {
            auto s = Node(y, current, current-> g + graph.weight(current->myself, y));
            auto foundInOpen = s.value_is_in(open);
            if (foundInOpen != nullptr) {
                if (foundInOpen->g > s.g) {
                    foundInOpen ->removeMyselfFrom(open);
                    open.push(new Node(s));
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

            open.push(new Node(s));
        }

    }

    return nullptr;
}

Node * Node::value_is_in(const priority_queue<Node *, vector<Node *>, function<bool(const Node*, const Node*) > > &destination) {
    auto copy = destination;
    while(!copy.empty()) {
        auto asd = copy.top();
        if (asd == this) {
            return asd;
        }
        copy.pop();
    }
    return nullptr;
}

bool Node::removeMyselfFrom(priority_queue<Node *, vector<Node *>, function<bool(const Node*, const Node*) > > &destination) {
    vector<Node *> reserve;
    auto addBack = [&reserve, &destination](){
        for (auto &i: reserve) {
            destination.push(i);
        }
    };
    while(!destination.empty()) {
        auto asd = destination.top();
        if (asd == this) {
            destination.pop();
            addBack();
            return true;
        }
        reserve.push_back(asd);
        destination.pop();
    }
    addBack();
    return false;
}
