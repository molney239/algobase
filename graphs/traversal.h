#ifndef ALGOBASE_TRAVERSAL_H
#define ALGOBASE_TRAVERSAL_H

#include <vector>
#include <queue>

namespace traversal {


    template<typename... Args>
    void dfs(std::vector<std::vector<unsigned>>& g, std::vector<bool>& visited, unsigned v,
                  void (*pre_func) (unsigned, Args...), Args&... args) {
        visited[v] = true;
        pre_func(v, args...);
        for (unsigned i = 0; i < g[v].size(); i++) {
            if (!visited[g[v][i]]) dfs(g, visited, g[v][i], pre_func, args...);
        }
    }


    template<typename... Args>
    void dfs(std::vector<std::vector<unsigned>>& g, std::vector<char>& color, unsigned v,
             void (*pre_func) (unsigned, Args...), Args&... args) {
        color[v] = 1;
        pre_func(v, args...);
        for (unsigned i = 0; i < g[v].size(); i++) {
            if (!color[g[v][i]]) dfs(g, color, g[v][i], pre_func, args...);
        }
        color[v] = 2;
    }


    template<typename... Args>
    void bfs(std::vector<std::vector<unsigned>>& g, std::vector<bool>& visited, unsigned v,
                  void (*pre_func) (unsigned, Args...), Args&... args) {
        std::queue<unsigned> q;
        q.push(v);

        while (!q.empty()) {
            unsigned p = q.front();
            q.pop();
            visited[p] = true;
            pre_func(p, args...);
            for (unsigned i = 0; i < g[p].size(); i++) {
                if (!visited[g[p][i]]) q.push(g[p][i]);
            }
        }
    }


}

#endif //ALGOBASE_TRAVERSAL_H