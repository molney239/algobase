#ifndef ALGOBASE_SEGMENT_TREE_H
#define ALGOBASE_SEGMENT_TREE_H

#include <vector>

namespace segment_tree {

    template<typename T>
    T sum(T a, T b) {
        return a + b;
    }

    template<typename T>
    void build(const std::vector<T>& v, std::vector<T>& tree, unsigned pos, unsigned l, unsigned r,
               T (*func)(T, T)) {
        if (l == r) tree[pos] = v[l];
        else {
            unsigned m = l + (r - l) / 2;
            build(v, tree, pos * 2 + 1, l, m, func);
            build(v, tree, pos * 2 + 2, m + 1, r, func);
            tree[pos] = func(tree[pos * 2 + 1], tree[pos * 2 + 2]);
        }
    }

    template<typename T>
    void build(const std::vector<T>& v, std::vector<T>& tree, T (*func)(T, T) = sum) {
        tree.resize(v.size() * 4);
        build(v, tree, 0, 0, v.size() - 1, func);
    }

    template<typename T>
    T get(const std::vector<T>& tree, unsigned pos, unsigned l, unsigned r,
            unsigned tl, unsigned tr,
            T (*func)(T, T), T neutral) {
        if (tr == -1) tr = tree.size() - 1;
        if (l <= tl && tr <= r) return tree[pos];
        if (r < tl || tr < l) return neutral;

        unsigned m = tl + (tr - tl) / 2;
        return func(get(tree, pos * 2 + 1, l, r, tl, m, func, neutral),
                    get(tree, pos * 2 + 2, l, r, m + 1, tr, func, neutral));
    }

    template<typename T>
    T get(const std::vector<T>& tree, unsigned l, unsigned r,
          T (*func)(T, T) = sum, T neutral = 0) {
        return get(tree, 0, l, r, 0, tree.size() / 4 - 1, func, neutral);
    }

    template<typename T>
    void update(std::vector<T>& tree, unsigned pos, unsigned l, unsigned r,
                  unsigned position, T value,
                  T (*func)(T, T)) {
        if (l == r && l == position) {
            tree[pos] = value;
            return;
        }
        if (position < l || r < position) return;

        unsigned m = l + (r - l) / 2;
        update(tree, pos * 2 + 1, l, m, position, value, func);
        update(tree, pos * 2 + 2, m + 1, r , position, value, func);
        tree[pos] = func(tree[pos * 2 + 1], tree[pos * 2 + 2]);
    }

    template<typename T>
    void update(std::vector<T>& tree, unsigned position, T value,
                T (*func)(T, T) = sum) {
        update(tree, 0, 0, tree.size() / 4 - 1, position, value, func);
    }

}

namespace lazy_propagation_st {

    template<typename T>
    T sum(T a, T b) {
        return a + b;
    }

    template<typename T>
    void build(const std::vector<T>& v, std::vector<T>& tree, std::vector<T>& mark,
               unsigned pos, unsigned l, unsigned r,
               T plug,
               T (*func)(T, T)) {
        mark[pos] = plug;
        if (l == r) {
            tree[pos] = v[l];
            return;
        }

        T m = (l + r) / 2;
        build(v, tree, mark, pos * 2 + 1, l, m, plug, func);
        build(v, tree, mark, pos * 2 + 2, m + 1, r, plug, func);
        tree[pos] = func(tree[pos * 2 + 1], tree[pos * 2 + 2]);
    }

    template<typename T>
    void build(const std::vector<T>& v, std::vector<T>& tree, std::vector<T>& mark,
               T plug = -1,
               T (*func)(T, T) = sum) {
        tree.resize(v.size() * 4);
        mark.resize(v.size() * 4);
        build(v, tree, mark, 0, 0, v.size() - 1, plug, func);
    }

    template<typename T>
    void propagate(std::vector<T>& tree, std::vector<T>& mark, unsigned pos,
                   unsigned l, unsigned r, T plug) {
        if (l == r) {
            tree[pos] = mark[pos];
            mark[pos] = plug;
            return;
        }
        mark[pos * 2 + 1] = mark[pos];
        mark[pos * 2 + 2] = mark[pos];
        tree[pos] = (r - l + 1) * mark[pos];
        mark[pos] = plug;
    }

    template<typename T>
    T get(std::vector<T>& tree, std::vector<T>& mark, unsigned l, unsigned r,
          unsigned pos, unsigned tl, unsigned tr,
          T neutral, T plug, T (*func)(T, T)) {
        if (tr < l || r < tl) return neutral;
        propagate(tree, mark, 0, 0, tree.size() / 4 - 1, plug);
        if (l <= tl && tr <= r) return tree[pos];

        T m = (tl + tr) / 2;
        return func(get(tree, mark, l, r, pos * 2 + 1, tl, m, neutral, plug, func),
                    get(tree, mark, l, r, pos * 2 + 2, m + 1, tr, neutral, plug, func));
    }

    template<typename T>
    T get(std::vector<T>& tree, std::vector<T>& mark, unsigned l, unsigned r,
          T neutral = 0, T plug = -1, T (*func)(T, T) = sum) {
        return get(tree, mark, l, r, 0, 0, tree.size() / 4 - 1, neutral, plug, func);
    }

    template<typename T>
    void update(std::vector<T>& tree, std::vector<T>& mark, unsigned l, unsigned r, T value,
                unsigned pos, unsigned tl, unsigned tr, T (*func)(T, T)) {
        if (tr < l || r < tl) return;

        if (l <= tl && tr <= r) {
            mark[pos] = value;
            return;
        }

        T m = (l + r) / 2;
        update(tree, mark, l, r, value, pos * 2 + 1, tl, m, func);
        update(tree, mark, l, r, value, pos * 2 + 2, m + 1, tr, func);
        tree[pos] = func(tree[pos * 2 + 2], tree[pos * 2 + 2]);
    }

}

#endif //ALGOBASE_SEGMENT_TREE_H