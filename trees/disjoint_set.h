#ifndef ALGOBASE_DISJOINT_SET_H
#define ALGOBASE_DISJOINT_SET_H

#include <vector>

namespace disjoint_set {

    void build(std::vector<unsigned>& parents, std::vector<unsigned>& size, unsigned n) {
        parents.resize(n);
        size.resize(n);
        for (int i = 0; i < n; i++) {
            parents[i] = i;
            size[i] = 1;
        }
    }

    unsigned find_set(std::vector<unsigned>& parents, unsigned v) {
        if (parents[v] != v) parents[v] = find_set(parents, parents[v]);
        return parents[v];
    }

    void union_sets(std::vector<unsigned>& parents, std::vector<unsigned>& size,
                    unsigned a, unsigned b) {
        a = find_set(parents, a);
        b = find_set(parents, b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        parents[b] = a;
        size[a] += size[b];
    }

}

#endif //ALGOBASE_DISJOINT_SET_H