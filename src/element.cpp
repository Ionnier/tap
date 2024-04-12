#include <element.h>

template <class T>
Element<T>::Element(const Group<T> *owner, const T &value, Element<T> *prev, Element<T> *next): owner(owner), value(value), prev(prev), next(next) {

}

template <class T>
std::ostream& operator<<(std::ostream& out, const Element<T> &aux) {
    out << "Element(value= " << aux.value << ", hasNext=" << (aux.next != nullptr) << ", hasPrev=" << (aux.prev != nullptr) << ")";
    return out;
}