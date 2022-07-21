#include <bits/stdc++.h>
using namespace std;

// trie

template<int k>
struct trie_node {

    trie_node() {
        children = new trie_node*[k];
        for (int i = 0; i < k; i++) children[i] = nullptr;
    }

    int count = 0, sum = 0;
    trie_node* *children;

};

template<int k>
struct trie {

    trie() {
        root = trie_node<k>();
    }

    void insert(string s) {
        insert(&root, s, 0);
    }

    bool remove(string s) {
        if (s.empty()) {
            if (root.count != 0) {
                sze--;
                root.count--;
                root.sum--;
                return true;
            } else return false;
        } else {
            return remove(&root, s, 0);
        }
    }

    int count(string s) {
        if (s.empty()) return root.count;
        return count(&root, s, 0);
    }

    void print() {
        string s;
        print(&root, s);
    }

    int size() {
        return sze;
    }

    bool empty() {
        return sze == 0;
    }

    trie_node<k>* get_root() {
        return &root;
    }

protected:

    int index(char c) {
        return c - 'a';
    }

    char get_char(int index) {
        return 'a' + index;
    }

    void insert(trie_node<k>* node, string& s, int pos) {
        assert(node != nullptr);
        if (pos >= s.length()) {
            sze++;
            node->count++;
            node->sum++;
            return;
        }

        if (node->children[index(s[pos])] == nullptr) {
            node->children[index(s[pos])] = new trie_node<k>();
        }
        insert(node->children[index(s[pos])], s, pos + 1);
        node->sum++;
    }

    bool remove(trie_node<k>* node, string& s, int pos) {
        if (node == nullptr) return false;
        if (pos == (int)s.length() - 1) {
            trie_node<k>* last = node->children[index(s[pos])];
            if (last != nullptr) {
                if (last->count != 0) {
                    sze--;
                    last->count--;
                    last->sum--;
                    if (last->sum == 0) {
                        delete last;
                        node->children[index(s[pos])] = nullptr;
                    }
                    return true;
                } else return false;
            } else return false;
        }

        if (remove(node->children[index(s[pos])], s, pos + 1)) {
            node->sum--;
            return true;
        } else return false;
    }

    int count(trie_node<k>* node, string& s, int pos) {
        if (node == nullptr) return 0;
        if (pos >= s.length()) return node->count;

        count(node->children[index(s[pos])], s, pos + 1);
    }

    void print(trie_node<k>* node, string& s) {
        assert(node != nullptr);
        for (int i = 0; i < node->count; i++) cout << s << "\n";
        for (int i = 0; i < k; i++) {
            if (node->children[i] != nullptr) {
                s += get_char(i);
                print(node->children[i], s);
                s.pop_back();
            }
        }
    }

    trie_node<k> root;
    int sze = 0;

};

// number trie

struct number_trie_node {

    number_trie_node() {

    }

    number_trie_node*& get(int bit) {
        if (!bit) return zero;
        return one;
    }

    int count = 0, sum = 0;

    number_trie_node* zero = nullptr;
    number_trie_node* one = nullptr;

};

template<typename T, int k>
struct number_trie {

    number_trie() {
        root = number_trie_node();
    }

    void insert(T n) {
        insert(&root, n, k - 1);
    }

    bool remove(T n) {
        return remove(&root, n, k - 1);
    }

    int count(T n) {
        return count(&root, n, k - 1);
    }

    void print() {
        T n = 0;
        print(&root, n, k - 1);
    }

    T max_xor(T n) {
        T res = 0;
        max_xor(&root, n, res, k - 1);
        return res;
    }

    int count_greater_equal(T n) {
        return count_greater_equal(&root, n, k - 1);
    }

    int size() {
        return sze;
    }

    bool empty() {
        return sze == 0;
    }

    number_trie_node* get_root() {
        return &root;
    }

protected:

    void insert(number_trie_node* node, T& n, int pos) {
        assert(node != nullptr);
        if (pos < 0) {
            sze++;
            node->count++;
            node->sum++;
            return;
        }

        if (node->get((n >> pos) & 1) == nullptr) {
            node->get((n >> pos) & 1) = new number_trie_node();
        }
        insert(node->get((n >> pos) & 1), n, pos - 1);
        node->sum++;
    }

    bool remove(number_trie_node* node, T& n, int pos) {
        if (node == nullptr) return false;
        bool is;
        if (pos == 0) {
            number_trie_node* last = node->get((n >> pos) & 1);
            if (last != nullptr) {
                sze--;
                last->count--;
                last->sum--;
                is = true;
            } else return false;
        } else is = remove(node->get((n >> pos) & 1), n, pos - 1);

        if (node->get((n >> pos) & 1) != nullptr && node->get((n >> pos) & 1)->sum == 0) {
            delete node->get((n >> pos) & 1);
            node->get((n >> pos) & 1) = nullptr;
        }
        node->sum -= is;
        return is;
    }

    int count(number_trie_node* node, T& n, int pos) {
        if (node == nullptr) return 0;
        if (pos < 0) return node->count;

        count(node->get((n >> pos) & 1),  n, pos - 1);
    }

    void print(number_trie_node* node, T& n, int pos) {
        assert(node != nullptr);
        for (int i = 0; i < node->count; i++) cout << n << "\n";
        if (node->zero != nullptr) {
            print(node->zero, n, pos - 1);
        }
        if (node->one != nullptr) {
            n |= (1 << pos);
            print(node->one, n, pos - 1);
            n ^= (1 << pos);
        }
    }

    void max_xor(number_trie_node* node, T& n, T& res, int pos) {
        if (pos < 0) return;
        if (node == nullptr) return;

        if ((n >> pos) & 1) {
            if (node->zero != nullptr) {
                res |= (1 << pos);
                max_xor(node->zero, n, res, pos - 1);
            } else max_xor(node->one, n, res, pos - 1);
        } else {
            if (node->one != nullptr) {
                res |= (1 << pos);
                max_xor(node->one, n, res, pos - 1);
            } else max_xor(node->zero, n, res, pos - 1);
        }
    }

    int count_greater_equal(number_trie_node* node, T& n, int pos) {
        if (node == nullptr) return 0;
        if (pos < 0) return node->count;

        if ((n >> pos) & 1) {
            return count_greater_equal(node->one, n, pos - 1);
        } else {
            return count_greater_equal(node->zero, n, pos - 1) + (node->one == nullptr ? 0 : node->one->sum);
        }
    }

    number_trie_node root;
    int sze = 0;

};

// hash

typedef unsigned long long ull;

struct hash_struct {

    hash_struct() {}

    hash_struct(ull hash, int length, int base) :
            hash(hash), length(length), base(base) {
        assert(length >= 0 && base >= 0);
    }

    ull hash = 0;
    int length = 0, base = 0;

};

struct my_hash {

    my_hash(ull MOD, ull P) : MOD(MOD), P(P) {
        pows.push_back(1);
    }

    template<typename T>
    hash_struct get_hash(const vector<T>& v) {
        extend_pows(v.size());

        ull h = 0;
        for (int i = 0; i < v.size(); i++) {
            h += pows[i] * (ull)v[i];
            h %= MOD;
        }

        return hash_struct(h, v.size(), 0);
    }

    template<typename T>
    vector<ull> get_prefix_hash(const vector<T>& v) {
        extend_pows(v.size());

        vector<ull> pref(v.size());
        for (int i = 0; i < v.size(); i++) {
            if (i > 0) pref[i] = pref[i - 1];
            pref[i] += pows[i] * (ull)(v[i]);
            pref[i] %= MOD;
        }

        return pref;
    }

    hash_struct get_sub_hash(const vector<ull>& prefix, int l, int r) {
        assert(0 <= min(l, r) && max(l, r) < prefix.size());

        return hash_struct((MOD + prefix[r] - (l == 0 ? 0 : prefix[l - 1])) % MOD, r - l + 1, l);
    }

    hash_struct normalize(hash_struct h, int last_pow) {
        assert(0 <= last_pow && h.base + h.length - 1 <= last_pow);

        extend_pows(last_pow + 1);
        int d = last_pow - (h.base + h.length - 1);

        return hash_struct((h.hash * pows[d]) % MOD, h.length, h.base + d);
    }

    bool equal(hash_struct h1, hash_struct h2) {
        if (h1.length != h2.length) return false;

        int d = max(h1.base + h1.length - 1, h2.base + h2.length - 1);
        h1 = normalize(h1, d);
        h2 = normalize(h2, d);

        return h1.hash == h2.hash;
    }

protected:

    void extend_pows(int n) {
        assert(0 <= n);
        while (pows.size() < n) pows.push_back((pows.back() * P) % MOD);
    }

    ull MOD, P;
    vector<ull> pows;

};

struct my_hash64 {

    my_hash64(ull P) : P(P) {
        pows.push_back(1);
    }

    template<typename T>
    hash_struct get_hash(const vector<T>& v) {
        extend_pows(v.size());

        ull h = 0;
        for (int i = 0; i < v.size(); i++) {
            h += pows[i] * (ull)v[i];
        }

        return hash_struct(h, v.size(), 0);
    }

    template<typename T>
    vector<ull> get_prefix_hash(const vector<T>& v) {
        extend_pows(v.size());

        vector<ull> pref(v.size());
        for (int i = 0; i < v.size(); i++) {
            if (i > 0) pref[i] = pref[i - 1];
            pref[i] += pows[i] * (ull)(v[i]);
        }

        return pref;
    }

    hash_struct get_sub_hash(const vector<ull>& prefix, int l, int r) {
        assert(0 <= min(l, r) && max(l, r) < prefix.size());

        return hash_struct(prefix[r] - (l == 0 ? 0 : prefix[l - 1]), r - l + 1, l);
    }

    hash_struct normalize(hash_struct h, int last_pow) {
        assert(0 <= last_pow && h.base + h.length - 1 <= last_pow);

        extend_pows(last_pow + 1);
        int d = last_pow - (h.base + h.length - 1);

        return hash_struct(h.hash * pows[d], h.length, h.base + d);
    }

    bool equal(hash_struct h1, hash_struct h2) {
        if (h1.length != h2.length) return false;

        int d = max(h1.base + h1.length - 1, h2.base + h2.length - 1);
        h1 = normalize(h1, d);
        h2 = normalize(h2, d);

        return h1.hash == h2.hash;
    }

protected:

    void extend_pows(int n) {
        assert(0 <= n);
        while (pows.size() < n) pows.push_back(pows.back() * P);
    }

    ull P;
    vector<ull> pows;

};
