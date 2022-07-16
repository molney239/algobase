#include <bits/stdc++.h>
using namespace std;

mt19937_64 rnd(chrono::duration_cast<chrono::nanoseconds>(chrono::system_clock::now().time_since_epoch()).count());

//treap

template<typename T>
struct treap_node {

    treap_node(T value) : value(value) {
        y = rnd();
    }

    void recalc() {
        size = 1 + get_size(left) + get_size(right);
    }

    T value;
    unsigned long long y;
    unsigned size = 1;

    treap_node<T>* left = nullptr;
    treap_node<T>* right = nullptr;

};

template<typename T>
unsigned get_size(treap_node<T>* node) {
    return (node == nullptr ? 0 : node->size);
}

template<typename T>
struct treap {

    treap() {

    }

    treap_node<T>* merge(treap_node<T>* a, treap_node<T>* b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
        assert(right(a)->value < left(b)->value);

        if (a->y > b->y) {
            a->right = merge(a->right, b);
            a->recalc();
            return a;
        } else {
            b->left = merge(a, b->left);
            b->recalc();
            return b;
        }
    }

    // first - < value, second - >= value
    pair<treap_node<T>*, treap_node<T>*> split_by_value(treap_node<T>* node, T value) {
        if (node == nullptr) return {nullptr, nullptr};
        if (node->value >= value) {
            auto p = split_by_value(node->left, value);
            node->left = p.second;
            node->recalc();
            return {p.first, node};
        } else {
            auto p = split_by_value(node->right, value);
            node->right = p.first;
            node->recalc();
            return {node, p.second};
        }
    }

    // first - k elements, second - other
    pair<treap_node<T>*, treap_node<T>*> split_by_size(treap_node<T>* node, unsigned k) {
        if (node == nullptr) return {nullptr, nullptr};
        if (get_size(node->left) + 1 > k) {
            auto p = split_by_size(node->left, k);
            node->left = p.second;
            node->recalc();
            return {p.first, node};
        } else {
            auto p = split_by_size(node->right, k - get_size(node->left) - 1);
            node->right = p.first;
            node->recalc();
            return {node, p.second};
        }
    }

    void insert(treap_node<T>* node) {
        auto p = split_by_value(root, node->value);
        if (left(p.second) == nullptr || left(p.second)->value != node->value) {
            root = merge(p.first, merge(node, p.second));
        } else root = merge(p.first, p.second);
    }

    void insert(T value) {
        insert(new treap_node<T>(value));
    }

    // returns treap with elements from [l; r)
    treap_node<T>* cut_by_value(T l, T r) {
        assert(l <= r);

        auto p1 = split_by_value(root, r);
        auto p2 = split_by_value(p1.first, l);
        root = merge(p2.first, p1.second);

        return p2.second;
    }

    // returns treap with indexes from [l; r)
    treap_node<T>* cut_by_size(unsigned l, unsigned r) {
        assert(l <= r && r <= get_size(root));

        auto p1 = split_by_size(root, r);
        auto p2 = split_by_size(p1.first, l);
        root = merge(p2.first, p1.second);

        return p2.second;
    }

    treap_node<T>* left(treap_node<T>* node) {
        if (node == nullptr) return nullptr;
        if (node->left == nullptr) return node;
        return left(node->left);
    }

    treap_node<T>* right(treap_node<T>* node) {
        if (node == nullptr) return nullptr;
        if (node->right == nullptr) return node;
        return right(node->right);
    }

    T get(unsigned position) {
        assert(position < get_size(root));

        auto p = split(root, position);
        T res = left(p.second)->value;
        root = merge(p.first, p.second);

        return res;
    }

    void print(treap_node<T>* node) {
        if (node == nullptr) return;
        print(node->left);
        cout << node->value << " ";
        print(node->right);
    }

    treap_node<T>* root = nullptr;

};

template<typename T>
struct implicit_treap {

    implicit_treap() {

    }

    treap_node<T>* merge(treap_node<T>* a, treap_node<T>* b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
        if (a->y > b->y) {
            a->right = merge(a->right, b);
            a->recalc();
            return a;
        } else {
            b->left = merge(a, b->left);
            b->recalc();
            return b;
        }
    }

    // first - k elements, second - other
    pair<treap_node<T>*, treap_node<T>*> split(treap_node<T>* node, unsigned k) {
        if (node == nullptr) return {nullptr, nullptr};
        if (get_size(node->left) + 1 > k) {
            auto p = split(node->left, k);
            node->left = p.second;
            node->recalc();
            return {p.first, node};
        } else {
            auto p = split(node->right, k - get_size(node->left) - 1);
            node->right = p.first;
            node->recalc();
            return {node, p.second};
        }
    }

    void insert(treap_node<T>* node, unsigned position) {
        assert(position <= get_size(root));
        auto p = split(root, position);
        root = merge(p.first, merge(node, p.second));
    }

    void insert(T value, unsigned position) {
        insert(new treap_node<T>(value), position);
    }

    treap_node<T>* cut(unsigned l, unsigned r) {
        assert(l <= r && r < get_size(root));

        auto p1 = split(root, r + 1);
        auto p2 = split(p1.first, l);
        root = merge(p2.first, p1.second);

        return p2.second;
    }

    treap_node<T>* left(treap_node<T>* node) {
        if (node == nullptr) return nullptr;
        if (node->left == nullptr) return node;
        return left(node->left);
    }

    treap_node<T>* right(treap_node<T>* node) {
        if (node == nullptr) return nullptr;
        if (node->right == nullptr) return node;
        return right(node->right);
    }

    T& operator[] (unsigned position) {
        assert(position < get_size(root));

        auto p = split(root, position);
        T& res = left(p.second)->value;
        root = merge(p.first, p.second);

        return res;
    }

    void print(treap_node<T>* node) {
        if (node == nullptr) return;
        print(node->left);
        cout << node->value << " ";
        print(node->right);
    }

    treap_node<T>* root = nullptr;

};

// fenwick tree

template<typename T>
struct fenwick {

    fenwick(unsigned n) : n(n) {
        tree.resize(n);
    }

    fenwick(unsigned n, vector<T>& v) : fenwick(n) {
        assert(n == v.size());
        for (unsigned i = 0; i < n; i++) {
            add(i, v[i]);
        }
    }

    T get(int l, int r) {
        assert(0 <= l && l <= r && r < n);
        return get_pref(r) - (l == 0 ? 0 : get_pref(l - 1));
    }

    void add(int position, T value) {
        assert(0 <= position && position < n);
        for (; position < n; position |= position + 1)
            tree[position] += value;
    }

protected:

    T get_pref(int r) {
        assert(0 <= r && r < n);
        T res = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            res += tree[r];
        return res;
    }

    unsigned n;
    vector<T> tree;

};

template<typename T>
struct fenwick_sum {

    fenwick_sum(unsigned n) : n(n), f_i(n), f_const(n) {

    }

    fenwick_sum(unsigned n, vector<T>& v) : fenwick_sum(n) {
        assert(n == v.size());
        for (unsigned i = 0; i < n; i++) {
            add(i, i, v[i]);
        }
    }

    T get(int l, int r) {
        assert(0 <= l && l <= r && r < n);

        return get_pref(r) - (l == 0 ? 0 : get_pref(l - 1));
    }

    void add(int l, int r, T value) {
        assert(0 <= l && l <= r && r < n);

        __add(f_i, l, r, value);
        __add(f_const, l, r, value * (1 - l));
        if (r + 1 < n) __add(f_const, r + 1, n - 1, value * (r - l + 1));
    }

protected:

    T get_pref(int r) {
        assert(0 <= r && r < n);

        return __get(f_i, r) * r + __get(f_const, r);
    }

    T __get(vector<T>& v, int position) {
        assert(0 <= position && position < n);

        T res = 0;
        for (; position < n; position = position | (position + 1))
            res += v[position];
        return res;
    }

    void __add_pref(vector<T>& v, int position, T value) {
        assert(0 <= position && position < n);

        for (; position >= 0; position = (position & (position + 1)) - 1)
            v[position] += value;
    }

    void __add(vector<T>& v, int l, int r, T value) {
        assert(0 <= l && l <= r && r < n);

        __add_pref(v, r, value);
        if (l > 0) __add_pref(v, l - 1, -value);
    }

    unsigned n;
    vector<T> f_i, f_const;

};

// 2D fenwick tree

template<typename T>
struct fenwick_2d {

    fenwick_2d(unsigned n, unsigned m) : n(n), m(m) {
        tree.assign(n, vector<T>(m));
    }

    fenwick_2d(unsigned n, unsigned m, vector<vector<T>>& v) : fenwick_2d(n, m) {
        assert(n == v.size());
        for (unsigned i = 0; i < n; i++) assert(m == v[i].size());

        for (unsigned i = 0; i < n; i++) {
            for (unsigned j = 0; j < m; j++) {
                add(i, j, v[i][j]);
            }
        }
    }

    T get(int i1, int j1, int i2, int j2) {
        assert(0 <= min(i1, j1) && i1 <= i2 && j1 <= j2 && i2 < n && j2 < m);
        return get_pref(i2, j2) +
                (i1 == 0 ? 0 : -get_pref(i1 - 1, j2)) +
                (j1 == 0 ? 0 : -get_pref(i2, j1 - 1)) +
                (i1 == 0 || j1 == 0 ? 0 : get_pref(i1 - 1, j1 - 1));
    }

    void add(int i, int j, T value) {
        assert(0 <= min(i, j) && i < n && j < m);

        for (int i1 = i; i1 < n; i1 = i1 | (i1 + 1)) {
            for (int j1 = j; j1 < m; j1 = j1 | (j1 + 1))
                tree[i1][j1] += value;
        }
    }

protected:

    T get_pref(int i, int j) {
        assert(0 <= min(i, j) && i < n && j <= m);

        T res = 0;
        for (int i1 = i; i1 >= 0; i1 = (i1 & (i1 + 1)) - 1) {
            for (int j1 = j; j1 >= 0; j1 = (j1 & (j1 + 1)) - 1)
                res += tree[i1][j1];
        }
        return res;
    }

    unsigned n, m;
    vector<vector<T>> tree;

};

template<typename T>
struct fenwick_sum_2d {

    fenwick_sum_2d(unsigned n, unsigned m) : n(n), m(m) {
        f_ij.assign(n, vector<T>(m, 0));
        f_i.assign(n, vector<T>(m, 0));
        f_j.assign(n, vector<T>(m, 0));
        f_const.assign(n, vector<T>(m, 0));
    }

    fenwick_sum_2d(unsigned n, unsigned m, vector<vector<T>>& v) : fenwick_sum_2d(n, m) {
        assert(n == v.size());
        for (unsigned i = 0; i < n; i++) assert(m == v[i].size());

        for (unsigned i = 0; i < n; i++) {
            for (unsigned j = 0; j < m; j++) {
                add(i, j, i, j, v[i][j]);
            }
        }
    }

    T get(int i1, int j1, int i2, int j2) {
        assert(0 <= min(i1, j1) && i1 <= i2 && j1 <= j2 && i2 < n && j2 < m);

        return  get_pref(i2, j2) +
                (i1 == 0 ? 0 : -get_pref(i1 - 1, j2)) +
                (j1 == 0 ? 0 : -get_pref(i2, j1 - 1)) +
                (i1 == 0 || j1 == 0 ? 0 : get_pref(i1 - 1, j1 - 1));
    }

    void add(int i1, int j1, int i2, int j2, T value) {
        assert(0 <= min(i1, j1) && i1 <= i2 && j1 <= j2 && i2 < n && j2 < m);

        __add(f_ij, i1, j1, i2, j2, value);
        __add(f_i, i1, j1, i2, j2, value * (1 - j1));
        __add(f_j, i1, j1, i2, j2, value * (1 - i1));
        __add(f_const, i1, j1, i2, j2, value * (i1 * j1 - i1 - j1 + 1));

        if (j2 + 1 < m) {
            __add(f_i, i1, j2 + 1, i2, m - 1, value * (j2 - j1 + 1));
            __add(f_const, i1, j2 + 1, i2, m - 1, value * (1 - i1) * (j2 - j1 + 1));
        }

        if (i2 + 1 < n) {
            __add(f_j, i2 + 1, j1, n - 1, j2, value * (i2 - i1 + 1));
            __add(f_const, i2 + 1, j1, n - 1, j2, value * (1 - j1) * (i2 - i1 + 1));
        }

        if (i2 + 1 < n && j2 + 1 < m) {
            __add(f_const, i2 + 1, j2 + 1, n - 1, m - 1, value * (i2 - i1 + 1) * (j2 - j1 + 1));
        }
    }

protected:

    T get_pref(int i, int j) {
        assert(0 <= min(i, j) && i < n && j < m);

        return  __get(f_ij, i, j) * i * j +
                __get(f_i, i, j) * i +
                __get(f_j, i, j) * j +
                __get(f_const, i, j);
    }

    T __get(vector<vector<T>>& v, int i, int j) {
        assert(0 <= min(i, j) && i < n && j < m);

        T res = 0;
        for (int i1 = i; i1 < n; i1 = i1 | (i1 + 1)) {
            for (int j1 = j; j1 < m; j1 = j1 | (j1 + 1))
                res += v[i1][j1];
        }
        return res;
    }

    void __add_pref(vector<vector<T>>& v, int i, int j, T value) {
        assert(0 <= min(i, j) && i < n && j < m);

        for (int i1 = i; i1 >= 0; i1 = (i1 & (i1 + 1)) - 1) {
            for (int j1 = j; j1 >= 0; j1 = (j1 & (j1 + 1)) - 1)
                v[i1][j1] += value;
        }
    }

    void __add(vector<vector<T>>& v, int i1, int j1, int i2, int j2, T value) {
        assert(0 <= min(i1, j1) && i1 <= i2 && j1 <= j2 && i2 < n && j2 < m);

        __add_pref(v, i2, j2, value);
        if (i1 > 0) __add_pref(v, i1 - 1, j2, -value);
        if (j1 > 0) __add_pref(v, i2, j1 - 1, -value);
        if (i1 > 0 && j1 > 0) __add_pref(v, i1 - 1, j1 - 1, value);
    }

    unsigned n, m;
    vector<vector<T>> f_ij, f_i, f_j, f_const;

};

// segment tree

template<typename T>
struct segment_tree {

    segment_tree(unsigned n, T neutral) : n(n), neutral(neutral) {
        tree.resize(n * 4, neutral);
        mark.resize(n * 4, neutral);
        marked.resize(n * 4, false);
    }

    segment_tree(const vector<T>& v, T neutral) : n(v.size()), neutral(neutral) {
        tree.resize(v.size() * 4);
        mark.resize(v.size() * 4, neutral);
        marked.resize(v.size() * 4, false);
        build(v, 0, 0, n - 1);
    }

    T get(int l, int r) {
        assert(0 <= l && l <= r && r < n);
        return get(l, r, 0, 0, n - 1);
    }

    void set(int l, int r, T value) {
        assert(0 <= l && l <= r && r < n);
        set(l, r, value, 0, 0, n - 1);
    }

protected:

    T merge(T a, T b) {
        return a + b;
    }

    void build(const vector<T>& v, int pos, int tl, int tr) {
        if (tl == tr) {
            tree[pos] = v[tl];
            return;
        }

        int m = (tl + tr) >> 1;
        build(v, pos * 2 + 1, tl, m);
        build(v, pos * 2 + 2, m + 1, tr);
        tree[pos] = merge(tree[pos * 2 + 1], tree[pos * 2 + 2]);
    }

    void push(int pos, int tl, int tr) {
        if (!marked[pos]) return;

        if (tl != tr) {
            int m = (tl + tr) >> 1;

            marked[pos * 2 + 1] = true;
            mark[pos * 2 + 1] = mark[pos];
            tree[pos * 2 + 1] = mark[pos] * (m - tl + 1);

            marked[pos * 2 + 2] = true;
            mark[pos * 2 + 2] = mark[pos];
            tree[pos * 2 + 2] = mark[pos] * (tr - m);
        }

        marked[pos] = false;
    }

    T get(int& l, int& r, int pos, int tl, int tr) {
        if (tr < l || r < tl) return neutral;
        if (l <= tl && tr <= r) return tree[pos];

        push(pos, tl, tr);
        int m = (tl + tr) >> 1;
        return merge(get(l, r, pos * 2 + 1, tl, m),
                     get(l, r, pos * 2 + 2, m + 1, tr));
    }

    void set(int& l, int& r, T& value, int pos, int tl, int tr) {
        if (tr < l || r < tl) return;
        push(pos, tl, tr);
        if (l <= tl && tr <= r) {
            marked[pos] = true;
            mark[pos] = value;
            tree[pos] = value * (tr - tl + 1);
            return;
        }

        int m = (tl + tr) >> 1;
        set(l, r, value, pos * 2 + 1, tl, m);
        set(l, r, value, pos * 2 + 2, m + 1, tr);
        tree[pos] = merge(tree[pos * 2 + 1], tree[pos * 2 + 2]);
    }

    int n;
    T neutral;

    vector<T> tree, mark;
    vector<bool> marked;

};
