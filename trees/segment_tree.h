#ifndef ALGOBASE_SEGMENT_TREE_H
#define ALGOBASE_SEGMENT_TREE_H

#include <vector>
#include <unordered_map>

template<typename T>
struct segment_tree {

    std::vector<T> tree, mark;
    std::vector<bool> is_marked;

    segment_tree(const std::vector<T>& v) {
        tree.assign(v.size() * 4, 0);
        mark.assign(v.size() * 4, 0);
        is_marked.assign(v.size() * 4, false);
        this->size = v.size();
        build(v, 0, 0, size - 1);
    }

    T get(unsigned l, unsigned r) {
        if (l > r) return 0;
        return get(l, min(r, size - 1), 0, 0, size - 1);
    }

    void update(unsigned l, unsigned r, T value) {
        if (l > r) return;
        update(l, min(r, size - 1), value, 0, 0, size - 1);
    }

    unsigned get_size() {
        return this->size;
    }

protected:

    unsigned size;

    void build(const std::vector<T>& v, int pos, int l, int r) {
        if (l == r) {
            tree[pos] = v[l];
            return;
        }

        int m = (l + r) / 2;
        build(v, pos * 2 + 1, l, m);
        build(v, pos * 2 + 2, m + 1, r);
        tree[pos] = tree[pos * 2 + 1] + tree[pos * 2 + 2];
    }

    void propagate(unsigned pos, unsigned l, unsigned r) {
        if (!is_marked[pos]) return;

        if (l < r) {
            unsigned m = (l + r) / 2;
            tree[pos * 2 + 1] = (m - l + 1) * mark[pos];
            mark[pos * 2 + 1] = mark[pos];
            is_marked[pos * 2 + 1] = true;

            tree[pos * 2 + 2] = (r - m) * mark[pos];
            mark[pos * 2 + 2] = mark[pos];
            is_marked[pos * 2 + 2] = true;
        }

        is_marked[pos] = false;
    }

    T get(unsigned l, unsigned r, unsigned pos, unsigned tl, unsigned tr) {
        if (tr < l || r < tl) return 0;
        propagate(pos, tl, tr);
        if (l <= tl && tr <= r) return tree[pos];

        unsigned m = (tl + tr) / 2;
        return get(l, r, pos * 2 + 1, tl, m) +
               get(l, r, pos * 2 + 2, m + 1, tr);
    }

    void update(unsigned l, unsigned r, T value, unsigned pos, unsigned tl, unsigned tr) {
        if (tr < l || r < tl) return;
        propagate(pos, tl, tr);
        if (l <= tl && tr <= r) {
            tree[pos] = (tr - tl + 1) * value;
            mark[pos] = value;
            is_marked[pos] = true;
            return;
        }

        unsigned m = (tl + tr) / 2;
        update(l, r, value, pos * 2 + 1, tl, m);
        update(l, r, value, pos * 2 + 2, m + 1, tr);
        tree[pos] = tree[pos * 2 + 1] + tree[pos * 2 + 2];
    }

};


template<typename T>
struct dynamic_segment_tree {

    dynamic_segment_tree(unsigned size) {
        this->size = size;
    }

    T get(unsigned l, unsigned r) {
        if (l > r) return 0;
        return get(l, min(r, size - 1), 0, 0, size - 1);
    }

    void update(unsigned l, unsigned r, T value) {
        if (l > r) return;
        update(l, min(r, size - 1), value, 0, 0, size - 1);
    }

    unsigned get_size() {
        return this->size;
    }

protected:

    unsigned size;

    std::unordered_map<unsigned, pair<T, pair<bool, T>>> tree;

    void propagate(unsigned pos, unsigned l, unsigned r) {
        if (!tree[pos].second.first) return;

        if (l < r) {
            unsigned m = (l + r) / 2;
            tree[pos * 2 + 1].first = (m - l + 1) * tree[pos].second.second;
            tree[pos * 2 + 1].second.second = tree[pos].second.second;
            tree[pos * 2 + 1].second.first = true;

            tree[pos * 2 + 2].first = (r - m) * tree[pos].second.second;
            tree[pos * 2 + 2].second.second = tree[pos].second.second;
            tree[pos * 2 + 2].second.first = true;
        }

        tree[pos].second.first = false;
    }

    T get(unsigned l, unsigned r, unsigned pos, unsigned tl, unsigned tr) {
        if (tr < l || r < tl) return 0;
        propagate(pos, tl, tr);
        if (l <= tl && tr <= r) return tree[pos].first;

        unsigned m = (tl + tr) / 2;
        return get(l, r, pos * 2 + 1, tl, m) +
               get(l, r, pos * 2 + 2, m + 1, tr);
    }

    void update(unsigned l, unsigned r, T value, unsigned pos, unsigned tl, unsigned tr) {
        if (tr < l || r < tl) return;
        propagate(pos, tl, tr);
        if (l <= tl && tr <= r) {
            tree[pos].first = (tr - tl + 1) * value;
            tree[pos].second.second = value;
            tree[pos].second.first = true;
            return;
        }

        unsigned m = (tl + tr) / 2;
        update(l, r, value, pos * 2 + 1, tl, m);
        update(l, r, value, pos * 2 + 2, m + 1, tr);
        tree[pos].first = tree[pos * 2 + 1].first + tree[pos * 2 + 2].first;
    }

};

#endif //ALGOBASE_SEGMENT_TREE_H