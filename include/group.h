#ifndef TAP_GROUP_H
#define TAP_GROUP_H
#include <vector>
#include <forward_def.h>
using namespace std;

template <class T>
class Group {
    Element<T> *first = nullptr;
    Element<T>* last = nullptr;
public:
    Group() = default;
    Group(const vector<T> &);
    ~Group();
    Group(const vector<Element<T> > &);
    void addElement(const T &t);

    Element<T>* getFirst();
    Element<T>* getLast();

    friend ostream& operator<<(ostream& out, const Group<T> &aux);
    vector<Element<T> > operator-(const Group<T> &aux);
    vector<Element<T> > u(const Group<T> &aux);

};
#endif //TAP_GROUP_H
