//
// Created by Dragos BAHRIM on 15.04.2024.
//

#ifndef TAP_BAG_H
#define TAP_BAG_H
#include <iostream>
#include <vector>
using namespace std;
template <typename T>
struct BinaryTree {
    T value = 0;
    struct BinaryTree *left;
    struct BinaryTree *right;

    explicit BinaryTree(const T &value = 0, struct BinaryTree *left = nullptr, struct BinaryTree* right = nullptr): value(value), left(left), right(right) {

    }

    friend ostream& operator<<(ostream& out, const BinaryTree<T> &tree) {
        out << "======== Begin Binary Tree ========" << endl;
        out << "Value (" << tree.value << ")" << endl;
        if (tree.left == nullptr) {
            out << "Has no left member" << endl;
        } else {
            out << "======== Begin left member ========" << endl;
            out << *(tree.left);
            out << "======== End  left  member ========" << endl;
        }
        if (tree.right == nullptr) {
            out << "Has no right member" << endl;
        } else {
            out << "======== Begin right member ========" << endl;
            out << *(tree.right);
            out << "======== End  right  member ========" << endl;
        }
        return out;
    }

    bool isValid() {
        if (this->right == nullptr || this->left == nullptr) {
            return true;
        }
        if (this->right == nullptr || this->left == nullptr) {
            return false;
        }
        return this->right->isValid() && this->left->isValid();
    }

    int getDegree() {
        if (this->right == nullptr && this->left == nullptr) {
            return 1;
        }
        return 1 + this->right->getDegree();
    }


};

template <typename T>
class PennantTree {
    T root_value;
    struct BinaryTree<T> *tree;
    PennantTree() = default;
public:
    PennantTree(const PennantTree<T>&aux) = delete;
    const PennantTree& operator=(const PennantTree<T>&aux) = delete;

    static PennantTree<T>* init(BinaryTree<T> *tree, const T &value) {
        if (tree != nullptr && !tree ->isValid()) {
            return nullptr;
        }
        auto s = new PennantTree<T>();
        s->root_value = value;
        s->tree = tree;
        return s;
    }

    static PennantTree<T>* reunion(PennantTree<T> *left, PennantTree<T> *right) {
        auto s = new PennantTree<T>();
        s->root_value = left->root_value;
        auto d = new BinaryTree<T>();
        d->value = right->root_value;
        d->left = left->tree;
        d->right = right->tree;
        s->tree = d;
        return s;
    }

    pair<PennantTree<T>*, PennantTree<T>*> split() {
        auto left = new PennantTree<T>();
        left -> root_value = this->root_value;
        left -> tree = this -> tree->left;
        auto right = new PennantTree<T>();
        right -> root_value = this->tree->value;
        right -> tree = this -> tree->right;
        return make_pair(left, right);
    }

    friend ostream& operator<<(ostream& out, const PennantTree<T> &aux) {
        out << "====== Begin Pennant Tree("<< aux.root_value << ")  ======" << endl;
        if (aux.tree != nullptr) {
            out << *(aux.tree);
        }
        out << "====== End Pennant Tree =======";
        return out;
    }

    static pair<PennantTree<T>*, PennantTree<T>*> FA(PennantTree<T>* a, PennantTree<T>* b, PennantTree<T>* ci) {
        int x = 0;
        if (a != nullptr) {
            x += 1;
        }
        if (b != nullptr) {
            x += 2;
        }
        if (ci != nullptr) {
            x += 4;
        }
        auto s = make_pair<PennantTree<T>*, PennantTree<T>*>(nullptr, nullptr);
        switch (x) {
            default:
                break;
            case 1:
                s = make_pair(a, nullptr);
                break;
            case 2:
                s = make_pair(b, nullptr);
                break;
            case 3:
                s = make_pair(nullptr, PennantTree<T>::reunion(a, b));
                break;
            case 4:
                s = make_pair(ci, nullptr);
                break;
            case 5:
                s = make_pair(nullptr, PennantTree<T>::reunion(a, ci));
                break;
            case 6:
                s = make_pair(nullptr, PennantTree<T>::reunion(b, ci));
                break;
            case 7:
                s = make_pair(a, PennantTree<T>::reunion(b, ci));
                break;
        }
        return s;
    }
};

template <typename T>
class Bag {
    vector<PennantTree<T> *> elements;
    void push_back(PennantTree<T> * aux) {
        for (int i = 0; i < elements.size(); i++) {
            if (elements[i] == nullptr) {
                elements[i] = aux;
                return;
            }
        }
        elements.push_back(aux);
    }
public:
    bool isEmpty() {
        return elements.empty();
    }
    vector<PennantTree<T> *>& getElements() {
        return elements;
    }
    PennantTree<T>* operator[](int index) {
        if (index >= elements.size() || index < 0) {
            return nullptr;
        }
        return elements[index];
    }

    int size() {
        return elements.size();
    }

    void insert(const T &x) {
        auto hey = PennantTree<T>::init(nullptr, x);
        auto k = 0;
        while (k < elements.size() && elements[k] != nullptr) {
            hey = PennantTree<T>::reunion(elements[k], hey);
            elements[k++] = nullptr;
        }
        if (k >= elements.size()) {
            elements.push_back(hey);
            return;
        }
        elements[k] = hey;
    }
    friend ostream& operator<<(ostream& out, const Bag &x) {
        out << "==== Begin Bag ====" << endl;
        for (auto current = x.elements.rbegin(); current != x.elements.rend(); current++) {
            if (*current == nullptr) {
                out << "Empty element" << endl;
                continue;
            }
            out << **current << endl;
        }
        out << "==== End   Bag ====" << endl;
        return out;
    }

    static Bag<T>* reunion(Bag<T> *S1, Bag<T> *S2) {
        PennantTree<T> *aux = nullptr;
        Bag *bigG = new Bag<T>();
        for (int i = 0; i < max(S1->size(), S2->size()); i++) {
            pair<PennantTree<T>*, PennantTree<T>*> asd = PennantTree<T>::FA((*S1)[i], (*S2)[i], aux);
            aux = asd.second;
            if (asd.first != nullptr) {
                bigG->push_back(asd.first);
            }
        }
        if (aux != nullptr) {
            bigG->push_back(aux);
        }
        return bigG;
    }

    static Bag<T>* split(Bag<T> *S1) {
        auto *bigG = new Bag<T>();
        auto y = (*S1)[0];
        S1->elements[0] = nullptr;
        for (int i = 1; i < S1->size(); i++) {
            if ((*S1)[i] != nullptr) {
                while (bigG->size() <= i - 1) {
                    bigG->insert(-1);
                }
                auto asd = (*S1)[i]->split();
                bigG->getElements()[i-1] = asd.second;
                S1->elements[i-1] = asd.first;
                S1->elements[i] = nullptr;
            }
        }
        if (y != nullptr) {
            S1->push_back(y);
        }
        return bigG;
    }

};
#endif //TAP_BAG_H
