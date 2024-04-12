#include <element.h>
#include <group.h>

template <class T>
Group<T>::Group(const vector<T> &initialSet) {
    for (auto &element: initialSet) {
        addElement(element);
    }
}

template <class T>
Group<T>::~Group() {
    auto current = first;
    const Group * group = nullptr;
    if (current != nullptr) {
        group = first ->owner;
    }
    while(current != nullptr && current->owner == group) {
        auto aux = current->next;
        delete current;
        current = aux;
    }
}

template <class T>
Group<T>::Group(const vector<Element<T> > &initialSet) {
    for (auto &element: initialSet) {
        addElement(element.value);
    }
}

template <class T>
void Group<T>::addElement(const T &t) {
        auto hey = new Element<T>(this, t);

        if (first == nullptr && last == nullptr) {
            first = hey;
            last = hey;
            return;
        }

        last->next = hey;
        hey->prev = last;
        last = hey;
        return;
    }
template <class T>
Element<T>* Group<T>::getFirst() {
    return first;
}
template <class T>
Element<T>* Group<T>::getLast() {
    return last;
}

template <class T>
ostream& operator<<(ostream& out, const Group<T> &aux) {
    out << "== Begin Group ==" << endl;
    auto current = aux.first;
    auto forta = current->owner;
    while (current != nullptr && (forta == current->owner)) {
        cout << *current << endl;
        current = current->next;
    }
    out << "== End Group ====";
    return out;
}

template <class T>
    vector<Element<T> > Group<T>::operator-(const Group<T> &aux) {
        vector<Element<T> > return_value;
        Element<T> *first_current = this->first;
        const Group* first_group = nullptr;
        if (first_current != nullptr) {
            first_group = first_current->owner;
        }
        while (first_current != nullptr && first_current->owner == first_group) {
            bool flag = false;

            Element<T>* current = aux.first;
            const Group* second_group = nullptr;
            if (current != nullptr) {
                second_group = current->owner;
            }
            while(current != nullptr && second_group == current->owner) {
                if (current->value == first_current->value) {
                    flag = true;
                    break;
                }
                current = current->next;
            }
            if (!flag) {
                return_value.push_back(*first_current);
            }
            first_current = first_current->next;
        }
        return return_value;
    }

    template <class T>
    vector<Element<T> > Group<T>::u(const Group<T> &aux) {
        vector<Element<T> > return_value;
        Element<T> *first_current = this->first;
        const Group* first_group = nullptr;
        if (first_current != nullptr) {
            first_group = first_current->owner;
        }
        while (first_current != nullptr && first_current->owner == first_group) {
            bool flag = false;
            Element<T>* current = aux.first;
            const Group* second_group = nullptr;
            if (current != nullptr) {
                second_group = current->owner;
            }
            while(current != nullptr && second_group == current->owner) {
                if (current->value == first_current->value) {
                    flag = true;
                    break;
                }
                current = current->next;
            }
            if (flag) {
                return_value.push_back(*first_current);
            }
            first_current = first_current->next;
        }
        return return_value;
    }