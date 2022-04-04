#ifndef ALGOBASE_FENWICK_TREE_H
#define ALGOBASE_FENWICK_TREE_H

#include <vector>

template<typename T>
struct fenwick_tree {

    std::vector<T> tree;

    fenwick_tree(unsigned n) {
        tree.assign(n, 0);
    }

    fenwick_tree(const vector<T>& v) {
        tree.assign(v.size(), 0);
        for (int i = 0; i < v.size(); i++) {
            increment(i, v[i]);
        }
    }

    T get(unsigned r) {
        cout << "get " << r << ": " << (r & (r + 1)) << "\n";
        if ((r & (r + 1)) == 0) return tree[r];
        return tree[r] + get((r & (r + 1)) - 1);
    }

    void increment(unsigned i, T value) {
        if (i > tree.size() - 1) return;
        tree[i] += value;
        increment((i | (i + 1)), value);
    }

};

#endif //ALGOBASE_FENWICK_TREE_H