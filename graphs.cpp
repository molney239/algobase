#include <bits/stdc++.h>
using namespace std;

// graph

struct graph_edge {

    graph_edge(int from, int to, int index) :
            from(from), to(to), index(index) {}

    int from, to, index;

};

#define graph_type vector<vector<graph_edge>>

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
        g_new[e.first].emplace_back(e.first, e.second, m_new++);
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
        if (color[pos] != color[e.to]) g_cond[color[pos]].emplace_back(color[pos], color[e.to], m_cond++);
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

// strongly-connected components

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
            g_rev[e.to].emplace_back(e.to, i, e.index);
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
            g_cond[color[pos]].emplace_back(color[pos], color[e.to], m_cond++);
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

        g[not_index(x)].emplace_back(not_index(x), y, m++);
        g[not_index(y)].emplace_back(not_index(y), x, m++);
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
