#ifndef ALGOBASE_SEGMENT_TREE_H
#define ALGOBASE_SEGMENT_TREE_H

#include <vector>

namespace segment_tree {

    template<typename T>
    T sum(T a, T b) {
        return a + b;
    }

    template<typename T>
    void build(const std::vector<T>& v, std::vector<T>& tree, T (*func)(T, T) = sum) {
        tree.resize(v.size() * 4);
        build(v, tree, 0, 0, v.size() - 1, func);
    }

    template<typename T>
    void build(const std::vector<T>& v, std::vector<T>& tree, size_t pos, size_t l, size_t r,
               T (*func)(T, T)) {
        if (l == r) tree[pos] = v[l];
        else {
            size_t m = l + (r - l) / 2;
            build(v, pos * 2 + 1, l, m);
            build(v, pos * 2 + 2, m + 1, r);
            tree[pos] = func(tree[pos * 2 + 1], tree[pos * 2 + 2]);
        }
    }

    template<typename T>
    T get(const std::vector<T>& tree, size_t l, size_t r,
          T (*func)(T, T) = sum, T neutral = 0) {
        return get(tree, 0, l, r, 0, tree.size() / 4 - 1, func, neutral);
    }

    template<typename T>
    T get(const std::vector<T>& tree, size_t pos, size_t l, size_t r,
          size_t tl, size_t tr,
          T (*func)(T, T), T neutral) {
        if (tr == -1) tr = tree.size() - 1;
        if (l <= tl && tr <= r) return tree[pos];
        if (r < tl || tr < l) return neutral;

        size_t m = tl + (tr - tl) / 2;
        return func(get(tree, pos * 2 + 1, l, r, tl, m, func, neutral),
                    get(tree, pos * 2 + 2, l, r, m + 1, tr, func, neutral));
    }

    template<typename T>
    void update(const std::vector<T>& tree, size_t position, T value,
                T (*func)(T, T) = sum) {
        update(tree, 0, 0, tree.size() / 4 - 1, position, value, func);
    }

    template<typename T>
    void update(const std::vector<T>& tree, size_t pos, size_t l, size_t r,
                size_t position, T value,
                T (*func)(T, T)) {
        if (l == r && l == position) {
            tree[pos] = value;
            return;
        }
        if (position < l || r < position) return;

        size_t m = l + (r - l) / 2;
        update(tree, pos * 2 + 1, l, m, position, value, func);
        update(tree, pos * 2 + 2, m + 1, r , position, value, func);
        tree[pos] = func(tree[pos * 2 + 1], tree[pos * 2 + 2]);
    }

};

#endif //ALGOBASE_SEGMENT_TREE_H