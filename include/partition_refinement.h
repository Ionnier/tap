#ifndef TAP_PARTITION_REFINEMENT_H
#define TAP_PARTITION_REFINEMENT_H
#include <element.h>
#include <group.h>
#include <algorithm>

template <class T>
class PartitionRefinement {
    vector<Group<T>*> elements;
    PartitionRefinement() = default;
public:
    static PartitionRefinement init(const vector<T> &initialSet);
    void refine(const vector<T> &set);
    Group<T> * first();
    bool isEmpty();
    bool remove(Element<T> *);
    friend std::ostream& operator<<(std::ostream& out, const PartitionRefinement<T> &aux) {
        out << "== Begin Partition ==" << endl;
        for (auto &element: aux.elements) {
            out << *element << endl;
        }
        out << "== End Partition ====" << endl;
        return out;
    }
};

template<class T>
bool PartitionRefinement<T>::remove(Element<T> *value) {
    if (elements.empty()) {
        return false;
    }

    for (auto y = elements.begin(); y < elements.end(); y++) {
        auto i = *y;
        auto current = i->getFirst();
        while (current != nullptr) {
            if (value == current) {
                if (i->getFirst() == i->getLast()) {
                    elements.erase(y);
                } else {
                    if (i->getFirst() == current) {
                        i->setFirst(current->next);
                    }
                    if (i->getLast() == current) {
                        i->setLast(current->prev);
                    }
                    if (current->prev != nullptr) {
                        current->prev->next = current->next;
                    }
                    if (current->next != nullptr) {
                        current->next->prev = current->prev;
                    }
                }
                return true;
            }
            current = current->next;
        }
    }

    return false;


    return false;
}

template <class T>
PartitionRefinement<T> PartitionRefinement<T>::init(const vector<T> &initialSet) {
    auto partition = PartitionRefinement();
    auto asd = new Group<T>(initialSet);
    partition.elements.push_back(asd);
    return partition;
}

template <class T>
void PartitionRefinement<T>::refine(const vector<T> &set) {
    auto current = elements.begin();
    while (current != elements.end()) {
        vector<Element<T> > dif = (**current) - set;
        vector<Element<T> > tog = (**current).u(set);
        if (dif.size() == 0 || tog.size() == 0) {
            current++;
            continue;
        }

        auto hey_dif = new Group<T>(dif);
        auto hey_tog = new Group<T>(tog);

        swap(hey_dif, hey_tog);

        hey_dif->getLast()->next = hey_tog->getFirst();
        hey_tog->getFirst()->prev = hey_dif->getLast();

        if ((**current).getFirst()->prev != nullptr) {
            (**current).getFirst()->prev->next = hey_dif->getFirst();
            hey_dif->getFirst()->prev = (**current).getFirst()->prev;
        }

        if ((**current).getLast()->next != nullptr) {
            (**current).getLast()->next->prev = hey_tog->getLast();
            hey_tog->getLast()->next = (**current).getLast()->next;
        }

        current = elements.insert(current, hey_tog);
        current = elements.insert(current, hey_dif);
        delete *(current + 2);
        elements.erase(current + 2);
        current += 2;
        break;
    }

}

template<class T>
Group<T>* PartitionRefinement<T>::first() {
    if (elements.empty()) {
        return nullptr;
    }
    return elements[0];
}

template<class T>
bool PartitionRefinement<T>::isEmpty() {
    return elements.empty();
}
#endif //TAP_PARTITION_REFINEMENT_H
