#include <bits/stdc++.h>
using namespace std;

// gcd

long long gcd(long long a, long long b) {
    if (a < b) swap(a, b);
    while (b > 0) {
        long long tmp = a;
        a = b;
        b = tmp % b;
    }
    return a;
}

long long lcm(long long a, long long b) {
    return (a * b) / gcd(a, b);
}

// sparse table

template<typename T>
struct sparse_table {

    sparse_table() {

    }

    sparse_table(const vector<T>& v) {
        n = v.size();
        lg_n = __lg(n) + 1;

        sparse.assign(lg_n, vector<T>(n));
        for (int i = 0; i < n; i++) sparse[0][i] = v[i];
        for (int l = 1; l < lg_n; l++) {
            for (int i = 0; i < n - (1 << l) + 1; i++) {
                sparse[l][i] = merge(sparse[l - 1][i], sparse[l - 1][i + (1 << (l - 1))]);
            }
        }
    }

    T get(int l, int r) {
        assert(0 <= l && l <= r && r < n);
        int t = __lg(r - l + 1);
        return merge(sparse[t][l], sparse[t][r - (1 << t) + 1]);
    }

protected:

    T merge(T a, T b) {
        return min(a, b);
    }

    int n = 0, lg_n = 0;
    vector<vector<T>> sparse;

};
