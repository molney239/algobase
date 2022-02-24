#ifndef ALGOBASE_DISJOINT_SET_H
#define ALGOBASE_DISJOINT_SET_H

#include <vector>

class DisjointSet {
public:

    DisjointSet() {

    }
    DisjointSet(size_t size) {
        this->parents = std::vector<size_t> (size);
        this->ranks = std::vector<size_t> (size);
        for (size_t i = 0; i < size; i++) {
            parents[i] = i;
            ranks[i] = 1;
        }
    }

    void make_set() {
        this->parents.push_back(this->size());
        this->ranks.push_back(1);
    }

    size_t find_set(size_t v) {
        if (v >= this->size()) return -1;
        if (parents[v] == v) return v;
        parents[v] = find_set(parents[v]);
        return parents[v];
    }

    void union_sets(size_t a, size_t b) {
        if (a >= this->size() || b >= this->size()) return;
        a = find_set(a);
        b = find_set(b);
        if (a == b) return;
        if (ranks[a] < ranks[b]) std::swap(a, b);
        parents[b] = a;
        ranks[a] += ranks[b];
    }

    size_t size() {
        return this->parents.size();
    }

protected:

    std::vector<size_t> parents;
    std::vector<size_t> ranks;

};

#endif //ALGOBASE_DISJOINT_SET_H