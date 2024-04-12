#include <partition_refinement.h>

template <class T>
PartitionRefinement<T> PartitionRefinement<T>::init(vector<T> &initialSet) {
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

        auto hey_dif = new Group<int>(dif);
        auto hey_tog = new Group<int>(tog);

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

template <class T>
std::ostream& operator<<(std::ostream& out, const PartitionRefinement<T> &aux) {
    cout << "== Begin Partition ==" << endl;
    for (auto &element: aux.elements) {
        cout << *element << endl;
    }
    cout << "== End Partition ====" << endl;
    return out;
}