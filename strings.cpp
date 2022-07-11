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

#define ull unsigned long long

namespace my_hash {

    struct hash_struct {

        hash_struct() {

        }

        hash_struct(ull hash1, ull hash2, int length, int base) :
                hash1(hash1), hash2(hash2), length(length), base(base) {

        }

        ull hash1 = 0, hash2 = 0;
        unsigned length = 0, base = 0;

    };

    template<ull MOD1, ull MOD2, ull P>
    struct hash {

        hash() {
            pows1.push_back(1);
            pows2.push_back(1);
        }

        hash_struct get_hash(vector<ull> v) {
            extend_pows(v.size());

            ull h1 = 0, h2 = 0;
            for (int i = 0; i < v.size(); i++) {
                h1 += v[i] * pows1[i];
                h1 %= MOD1;
                h2 += v[i] * pows2[i];
                h2 %= MOD2;
            }

            return hash_struct(h1, h2, v.size(), 0);
        }

        vector<hash_struct> get_prefix_hash(vector<ull> v) {
            extend_pows(v.size());

            vector<hash_struct> res(v.size());
            for (int i = 0; i < v.size(); i++) {
                res[i].length = i + 1;
                if (i > 0) {
                    res[i].hash1 = res[i - 1].hash1;
                    res[i].hash2 = res[i - 1].hash2;
                }

                res[i].hash1 += v[i] * pows1[i];
                res[i].hash1 %= MOD1;
                res[i].hash2 += v[i] * pows2[i];
                res[i].hash2 %= MOD2;
            }

            return res;
        }

        hash_struct get_sub_hash(vector<hash_struct> prefix_hash, unsigned l, unsigned r) {
            assert(l < prefix_hash.size() && r < prefix_hash.size());

            return hash_struct(
                    (MOD1 + prefix_hash[r].hash1 - (l == 0 ? 0 : prefix_hash[l - 1].hash1)) % MOD1,
                    (MOD2 + prefix_hash[r].hash2 - (l == 0 ? 0 : prefix_hash[l - 1].hash2)) % MOD2,
                    r - l + 1, l);
        }

        hash_struct normalize(hash_struct h, unsigned last_pow) {
            assert(h.base + h.length - 1 <= last_pow);

            extend_pows(last_pow + 1);
            unsigned d = last_pow - (h.base + h.length - 1);

            return hash_struct(
                    (h.hash1 * pows1[d]) % MOD1,
                    (h.hash2 * pows2[d]) % MOD2,
                    h.length, h.base + d);
        }

        bool equal(hash_struct h1, hash_struct h2) {
            if (h1.length != h2.length) return false;

            unsigned d = max(h1.base + h1.length - 1, h2.base + h2.length - 1);
            h1 = normalize(h1, d);
            h2 = normalize(h2, d);

            return h1.hash1 == h2.hash1 && h1.hash2 == h2.hash2;
        }

        vector<ull> convert(string s) {
            vector<ull> v(s.length());
            for (int i = 0; i < s.length(); i++) v[i] = s[i] - 'a' + 1;
            return v;
        }

    protected:

        void extend_pows(int n) {
            while (pows1.size() < n) pows1.push_back((pows1.back() * P) % MOD1);
            while (pows2.size() < n) pows2.push_back((pows2.back() * P) % MOD2);
        }

        vector<ull> pows1, pows2;

    };

}
