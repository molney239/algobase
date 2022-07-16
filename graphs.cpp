#include <bits/stdc++.h>
using namespace std;

// graph

struct graph_edge {

    graph_edge() {}

    graph_edge(int to) : to(to) {}

    int from, to, index, cost;

};

typedef vector<vector<graph_edge>> graph_type;

// multi edges

graph_type remove_multi_edges(graph_type& g) {
    int n = g.size();
    set<pair<int, int>> s;
    for (int i = 0; i < n; i++) {
        for (auto e : g[i]) {
            s.emplace(e.from, e.to);
        }
    }

    graph_type g_new(n);
    int m_new = 0;
    for (auto e : s) {
        g_new[e.first].emplace_back();
        g_new[e.first].back().from = e.first;
        g_new[e.first].back().to = e.second;
        g_new[e.first].back().index = m_new++;
    }

    return g_new;
}

// topological sort

void __topsort(graph_type& g, vector<bool>& visited, vector<int>& ans, int pos) {
    visited[pos] = true;
    for (auto e : g[pos]) {
        if (!visited[e.to]) {
            __topsort(g, visited, ans, e.to);
        }
    }
    ans.push_back(pos);
}

vector<int> topsort(graph_type& g) {
    int n = g.size();
    vector<bool> visited(n, false);
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            __topsort(g, visited, ans, i);
        }
    }
    reverse(ans.begin(), ans.end());

    return ans;
}

// bridges

void __find_bridges(graph_type& g, vector<bool>& visited, vector<bool>& is_bridge,
                    vector<int>& h, vector<int>& up, int pos, int parent, int d) {
    visited[pos] = true;
    h[pos] = d;
    up[pos] = d;
    for (auto e : g[pos]) {
        if (e.to == parent) continue;
        if (visited[e.to]) {
            up[pos] = min(up[pos], h[e.to]);
        } else {
            __find_bridges(g, visited, is_bridge, h, up, e.to, pos, d + 1);
            up[pos] = min(up[pos], up[e.to]);
            if (h[e.to] <= up[e.to]) is_bridge[e.index] = true;
        }
    }
}

vector<bool> find_bridges(graph_type& g) {
    int n = g.size(), m = 0;
    for (auto v : g) m += v.size();

    vector<bool> visited(n, false), is_bridge(m, false);
    vector<int> h(n, 0), up(n, 0);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) __find_bridges(g, visited, is_bridge, h, up, i, -1, 0);
    }

    return is_bridge;
}

// edge biconnected components

void __edge_biconnected_color(graph_type& g, vector<int>& color, vector<bool>& is_bridge, int pos, int c) {
    color[pos] = c;
    for (auto e : g[pos]) {
        if (is_bridge[e.index]) continue;
        if (color[e.to] == -1) __edge_biconnected_color(g, color, is_bridge, e.to, c);
    }
}

pair<vector<int>, int> edge_biconnected_color(graph_type& g) {
    int n = g.size();
    vector<int> color(n, -1);
    vector<bool> is_bridge = find_bridges(g);
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) __edge_biconnected_color(g, color, is_bridge, i, c++);
    }

    return {color, c};
}

void __edge_biconnected_condense(graph_type& g, vector<bool>& visited, vector<int>& color, graph_type& g_cond, int pos, int m_cond) {
    visited[pos] = true;
    for (auto e : g[pos]) {
        if (color[pos] != color[e.to]) {
            g_cond[color[pos]].emplace_back();
            g_cond[color[pos]].back().from = color[pos];
            g_cond[color[pos]].back().to = color[e.to];
            g_cond[color[pos]].back().index = m_cond++;
        }
        if (!visited[e.to]) __edge_biconnected_condense(g, visited, color, g_cond, e.to, m_cond);
    }
}

graph_type edge_biconnected_condense(graph_type& g) {
    int n = g.size();
    graph_type g_cond(n);
    vector<int> color = edge_biconnected_color(g).first;
    vector<bool> visited(n, false);
    int m_cond = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) __edge_biconnected_condense(g, visited, color, g_cond, i, m_cond);
    }

    return g_cond;
}

// strongly connected components

void __scc_color(graph_type& g, vector<int>& color, int pos, int c) {
    color[pos] = c;
    for (auto e : g[pos]) {
        if (color[e.to] == -1) {
            __scc_color(g, color, e.to, c);
        }
    }
}

pair<vector<int>, int> scc_color(graph_type& g) {
    int n = g.size();
    graph_type g_rev(n);
    for (int i = 0; i < n; i++) {
        for (auto e : g[i]) {
            g_rev[e.to].emplace_back();
            g_rev[e.to].back().from = e.to;
            g_rev[e.to].back().to = i;
            g_rev[e.to].back().index = e.index;
        }
    }

    vector<int> sorted = topsort(g_rev);
    vector<int> color(n, -1);
    int c = 0;
    for (int i = 0; i < n; i++) {
        int p = sorted[i];
        if (color[p] == -1) {
            __scc_color(g, color, p, c++);
        }
    }

    return {color, c};
}

void __scc_condense(graph_type& g, vector<bool>& visited, vector<int>& color, graph_type& g_cond, int pos, int& m_cond) {
    visited[pos] = true;
    for (auto e : g[pos]) {
        if (color[pos] != color[e.to]) {
            g_cond[color[pos]].emplace_back();
            g_cond[color[pos]].back().from = color[pos];
            g_cond[color[pos]].back().to = color[e.to];
            g_cond[color[pos]].back() = m_cond++;
        }
        if (!visited[e.to]) {
            __scc_condense(g, visited, color, g_cond, e.to, m_cond);
        }
    }
}

graph_type scc_condense(graph_type& g) {
    int n = g.size();
    auto r = scc_color(g);

    graph_type g_cond(r.second);
    vector<bool> visited(n, false);
    int m_cond = 0;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            __scc_condense(g, visited, r.first, g_cond, i, m_cond);
        }
    }
    remove_multi_edges(g_cond);

    return g_cond;
}

// 2-SAT

struct two_sat {

    two_sat() {

    }

    two_sat(int n) : n(n) {
        g.resize(n * 2);
    }

    void add(int x, bool is_x, int y, bool is_y) {
        if (is_x) x += n;
        if (is_y) y += n;

        g[not_index(x)].emplace_back();
        g[not_index(x)].back().from = not_index(x);
        g[not_index(x)].back().to = y;
        g[not_index(x)].back().index = m++;

        g[not_index(y)].emplace_back();
        g[not_index(y)].back().from = not_index(y);
        g[not_index(y)].back().to = x;
        g[not_index(y)].back().index = m++;
    }

    bool has_solution() {
        auto r = scc_color(g);
        for (int i = 0; i < n; i++) {
            if (r.first[i] == r.first[i + n]) return false;
        }
        return true;
    }

    vector<bool> find_solution() {
        assert(has_solution());

        auto r = scc_color(g);
        vector<vector<int>> components(r.second);
        for (int i = 0; i < n * 2; i++) {
            components[r.first[i]].push_back(i);
        }

        graph_type scc = scc_condense(g);
        vector<int> sorted = topsort(scc);

        vector<bool> ans(n, false);
        for (int i = 0; i < sorted.size(); i++) {
            for (int j = 0; j < components[sorted[i]].size(); j++) {
                int p = components[sorted[i]][j];
                if (p < n) ans[p] = false;
                else ans[p - n] = true;
            }
        }

        return ans;
    }

    int size() {
        return n;
    }

protected:

    int not_index(int ind) {
        if (ind < n) return ind + n;
        return ind - n;
    }

    int n = 0, m = 0;
    graph_type g;

};

// level ancestor

struct level_ancestor_binsearch {

    level_ancestor_binsearch(const graph_type& g, int root) {
        n = g.size();
        level.resize(n);
        dist.resize(n);
        tin.resize(n);

        vector<bool> visited(n, false);
        int t = 0;
        build(g, visited, root, 0, t);
        for (int i = 0; i < n; i++) {
            if (!visited[i]) build(g, visited, i, 0, t);
        }

        while (level.back().empty()) level.pop_back();
        level.shrink_to_fit();

        for (int i = 0; i < level.size(); i++) level[i].shrink_to_fit();
    }

    int get(int v, int k) {
        assert(0 <= v && v < n && 0 <= k);
        if (k > dist[v]) return -1;

        int l = 0, r = (int)level[dist[v] - k].size() - 1;
        while (l < r - 1) {
            int m = (l + r) >> 1;

            if (tin[level[dist[v] - k][m]] < tin[v]) l = m;
            else r = m;
        }

        if (tin[level[dist[v] - k][r]] < tin[v]) return level[dist[v] - k][r];
        else return level[dist[v] - k][l];
    }

protected:

    void build(const graph_type& g, vector<bool>& visited, int pos, int d, int& t) {
        visited[pos] = true;
        level[d].push_back(pos);
        dist[pos] = d;
        tin[pos] = t++;

        for (auto& e : g[pos]) {
            if (!visited[e.to]) {
                build(g, visited, e.to, d + 1, t);
            }
        }
    }

    int n;
    vector<vector<int>> level;
    vector<int> dist, tin;

};

struct level_ancestor_binups {

    level_ancestor_binups(const graph_type& g, int root) {
        assert(0 <= root && root < g.size());

        n = g.size();
        lg_n = __lg(n) + 1;

        parent.resize(n, -1);
        vector<bool> visited(n, false);
        parents(g, visited, root);
        for (int i = 0; i < n; i++) {
            if (!visited[i]) parents(g, visited, i);
        }

        binup.resize(lg_n, vector<int>(n, -1));
        for (int i = 0; i < n; i++) binup[0][i] = parent[i];
        for (int l = 1; l < lg_n; l++) {
            for (int i = 0; i < n; i++) {
                if (binup[l - 1][i] == -1) binup[l][i] = -1;
                else binup[l][i] = binup[l - 1][binup[l - 1][i]];
            }
        }
    }

    int get(int v, int k) {
        assert(0 <= v && v < n && 0 <= k);
        if (k == 0) return v;

        for (int l = lg_n - 1; l >= 0; l--) {
            if ((1 << l) < k) {
                if (v != -1) v = binup[l][v];
                k -= (1 << l);
            }
        }

        if (v == -1) return -1;
        else return binup[0][v];
    }

protected:

    void parents(const graph_type& g, vector<bool>& visited, int pos) {
        visited[pos] = true;
        for (auto& e : g[pos]) {
            if (!visited[e.to]) {
                parent[e.to] = pos;
                parents(g, visited, e.to);
            }
        }
    }

    int n, lg_n;
    vector<int> parent;
    vector<vector<int>> binup;

};

// LCA

struct lca_binups {

    lca_binups(const graph_type& g, int root) {
        assert(0 <= root && root < g.size());
        n = g.size();
        lg_n = __lg(n) + 1;

        dist.resize(n);

        vector<bool> visited(n, false);
        vector<int> parent(n, -1);
        dfs(g, visited, parent, root, 0);
        for (int i = 0; i < n; i++) {
            if (!visited[i]) dfs(g, visited, parent, i, 0);
        }

        binups.resize(lg_n, vector<int>(n));
        for (int i = 0; i < n; i++) binups[0][i] = parent[i];
        for (int l = 1; l < lg_n; l++) {
            for (int i = 0; i < n; i++) {
                if (binups[l - 1][i] == -1) binups[l][i] = -1;
                else binups[l][i] = binups[l - 1][binups[l - 1][i]];
            }
        }
    }

    int get(int a, int b) {
        assert(0 <= min(a, b) && max(a, b) < n);

        if (dist[a] > dist[b]) swap(a, b);
        if (dist[a] != dist[b]) {
            int k = dist[b] - dist[a];
            for (int l = lg_n - 1; l >= 0; l--) {
                if ((1 << l) < k) {
                    b = binups[l][b];
                    k -= (1 << l);
                }
            }
            b = binups[0][b];
        }

        if (a == b) return a;

        for (int l = lg_n - 1; l >= 0; l--) {
            if (binups[l][a] != binups[l][b]) {
                a = binups[l][a];
                b = binups[l][b];
            }
        }
        return binups[0][a];
    }

protected:

    void dfs(const graph_type& g, vector<bool>& visited, vector<int>& parent, int pos, int d) {
        visited[pos] = true;
        dist[pos] = d;

        for (auto e : g[pos]) {
            if (!visited[e.to]) {
                parent[e.to] = pos;
                dfs(g, visited, parent, e.to, d + 1);
            }
        }
    }

    int n, lg_n;
    vector<vector<int>> binups;
    vector<int> dist;

};

struct lca_segment_tree {

    lca_segment_tree(const graph_type& g, int root) {
        assert(0 <= root && root < g.size());
        n = g.size();

        tin.resize(n);

        vector<bool> visited(n, false);
        int t = 0;
        eulerian_tour(g, visited, root, 0, t);

        tree.resize(d.size() * 4);
        build(0, 0, (int)d.size() - 1);
    }

    int get(int a, int b) {
        assert(0 <= min(a, b) && max(a, b) < n);

        int t1 = min(tin[a], tin[b]), t2 = max(tin[a], tin[b]);
        return vertices[get(t1, t2, 0, 0, (int)d.size() - 1)];
    }

protected:

    void eulerian_tour(const graph_type& g, vector<bool>& visited, int pos, int dist, int& t) {
        visited[pos] = true;

        d.emplace_back(dist);
        vertices.emplace_back(pos);
        tin[pos] = t++;

        for (auto e : g[pos]) {
            if (!visited[e.to]) {
                eulerian_tour(g, visited, e.to, dist + 1, t);

                d.emplace_back(dist);
                vertices.emplace_back(pos);
                t++;
            }
        }
    }

    inline int merge(int a, int b) {
        if (a == -1) return b;
        if (b == -1) return a;
        if (d[a] < d[b]) return a;
        return b;
    }

    void build(int pos, int tl, int tr) {
        if (tl == tr) {
            tree[pos] = tl;
            return;
        }

        int m = (tl + tr) >> 1;
        build(pos * 2 + 1, tl, m);
        build(pos * 2 + 2, m + 1, tr);
        tree[pos] = merge(tree[pos * 2 + 1], tree[pos * 2 + 2]);
    }

    int get(int& l, int& r, int pos, int tl, int tr) {
        if (tr < l || r < tl) return -1;
        if (l <= tl && tr <= r) return tree[pos];

        int m = (tl + tr) >> 1;
        return merge(get(l, r, pos * 2 + 1, tl, m),
                     get(l, r, pos * 2 + 2, m + 1, tr));
    }

    int n;
    vector<int> d, vertices, tin;
    vector<int> tree;

};

struct lca_sparse_table {

    lca_sparse_table(const graph_type& g, int root) {
        assert(0 <= root && root < g.size());
        n = g.size();

        tin.resize(n);

        vector<bool> visited(n, false);
        int t = 0;
        eulerian_tour(g, visited, root, 0, t);

        lg_t = __lg(t) + 1;
        sparse.assign(lg_t, vector<int>(t));
        for (int i = 0; i < t; i++) sparse[0][i] = i;
        for (int l = 1; l < lg_t; l++) {
            for (int i = 0; i < t - (1 << l) + 1; i++) {
                sparse[l][i] = merge(sparse[l - 1][i], sparse[l - 1][i + (1 << (l - 1))]);
            }
        }
    }

    int get(int a, int b) {
        assert(0 <= min(a, b) && max(a, b) < n);

        int t1 = min(tin[a], tin[b]), t2 = max(tin[a], tin[b]);
        return vertices[_get(t1, t2)];
    }

protected:

    void eulerian_tour(const graph_type& g, vector<bool>& visited, int pos, int dist, int& t) {
        visited[pos] = true;

        d.emplace_back(dist);
        vertices.emplace_back(pos);
        tin[pos] = t++;

        for (auto e : g[pos]) {
            if (!visited[e.to]) {
                eulerian_tour(g, visited, e.to, dist + 1, t);

                d.emplace_back(dist);
                vertices.emplace_back(pos);
                t++;
            }
        }
    }

    inline int merge(int a, int b) {
        if (a == -1) return b;
        if (b == -1) return a;
        if (d[a] < d[b]) return a;
        return b;
    }

    int _get(int l, int r) {
        int t = __lg(r - l + 1);
        return merge(sparse[t][l], sparse[t][r - (1 << t) + 1]);
    }

    int n, lg_t;
    vector<int> d, vertices, tin;
    vector<vector<int>> sparse;

};

// tree path queries

struct tree_path_queries {

    tree_path_queries(const graph_type& g, int root) {
        assert(0 <= root && root < g.size());
        n = g.size();
        lg_n = __lg(n) + 1;

        dist.resize(n);

        vector<bool> visited(n, false);
        vector<int> parent(n, -1);
        vector<int> parent_func(n, 1e9);
        dfs(g, visited, parent, parent_func, root, 0);
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                dfs(g, visited, parent, parent_func, i, 0);
            }
        }

        binups_parent.resize(lg_n, vector<int>(n));
        for (int i = 0; i < n; i++) binups_parent[0][i] = parent[i];
        for (int l = 1; l < lg_n; l++) {
            for (int i = 0; i < n; i++) {
                if (binups_parent[l - 1][i] == -1) binups_parent[l][i] = -1;
                else binups_parent[l][i] = binups_parent[l - 1][binups_parent[l - 1][i]];
            }
        }

        binups_func.resize(lg_n, vector<int>(n));
        for (int i = 0; i < n; i++) binups_func[0][i] = parent_func[i];
        for (int l = 1; l < lg_n; l++) {
            for (int i = 0; i < n; i++) {
                if (binups_parent[l - 1][i] == -1) binups_func[l][i] = binups_func[l - 1][i];
                else binups_func[l][i] = merge(binups_func[l - 1][i], binups_func[l - 1][binups_parent[l - 1][i]]);
            }
        }
    }

    int get(int a, int b) {
        assert(0 <= min(a, b) && max(a, b) < n);

        int lca_ab = lca(a, b);
        int res = 1e9;

        if (a != lca_ab) {
            for (int l = lg_n - 1; l >= 0; l--) {
                if (dist[a] - (1 << l) > dist[lca_ab]) {
                    res = merge(res, binups_func[l][a]);
                    a = binups_parent[l][a];
                }
            }
            res = merge(res, binups_func[0][a]);
        }

        if (b != lca_ab) {
            for (int l = lg_n - 1; l >= 0; l--) {
                if (dist[b] - (1 << l) > dist[lca_ab]) {
                    res = merge(res, binups_func[l][b]);
                    b = binups_parent[l][b];
                }
            }
            res = merge(res, binups_func[0][b]);
        }

        return res;
    }

protected:

    int lca(int a, int b) {
        assert(0 <= min(a, b) && max(a, b) <= n);

        if (dist[a] > dist[b]) swap(a, b);
        if (dist[a] != dist[b]) {
            int k = dist[b] - dist[a];
            for (int l = lg_n - 1; l >= 0; l--) {
                if ((1 << l) < k) {
                    b = binups_parent[l][b];
                    k -= (1 << l);
                }
            }
            b = binups_parent[0][b];
        }

        if (a == b) return a;

        for (int l = lg_n - 1; l >= 0; l--) {
            if (binups_parent[l][a] != binups_parent[l][b]) {
                a = binups_parent[l][a];
                b = binups_parent[l][b];
            }
        }
        return binups_parent[0][a];
    }

    int merge(int a, int b) {
        return min(a, b);
    }

    void dfs(const graph_type& g, vector<bool>& visited, vector<int>& parent, vector<int>& parent_func, int pos, int d) {
        visited[pos] = true;
        dist[pos] = d;

        for (auto e : g[pos]) {
            if (!visited[e.to]) {
                parent[e.to] = pos;
                parent_func[e.to] = e.cost;
                dfs(g, visited, parent, parent_func, e.to, d + 1);
            }
        }
    }

    int n, lg_n;
    vector<vector<int>> binups_parent, binups_func;
    vector<int> dist;

};
