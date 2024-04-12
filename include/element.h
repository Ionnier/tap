#ifndef TAP_ELEMENT_H
#define TAP_ELEMENT_H
#include <iostream>
#include <forward_def.h>

template<typename T>
std::ostream& operator<<(std::ostream& out, const Element<T> &aux);
template <class T>
struct Element {
    T value;
    const Group<T> *owner;
    Element<T> *next;
    Element<T> *prev;
    Element(const Group<T> *owner, const T &value, Element<T> *prev = nullptr, Element<T> *next = nullptr);

    ~Element() = default;

    friend std::ostream& operator<< <>(std::ostream& out, const Element<T> &aux);
};
#endif //TAP_ELEMENT_H
