#ifndef TAP_PARTITION_REFINEMENT_H
#define TAP_PARTITION_REFINEMENT_H
#include <element.h>
#include <group.h>
template <class T>
class Element;

template <class T>
class PartitionRefinement {
    vector<Group<T>*> elements;
    PartitionRefinement() = default;
public:
    static PartitionRefinement init(vector<T> &initialSet);
    void refine(const vector<T> &set);
    friend std::ostream& operator<<(std::ostream& out, const PartitionRefinement<T> &aux);
};
#endif //TAP_PARTITION_REFINEMENT_H
