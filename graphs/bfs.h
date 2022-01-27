#ifndef ALGOBASE_BFS_H
#define ALGOBASE_BFS_H

#include <queue>

template<typename T, typename... Args>
void bfs_matrix(std::vector<std::vector<T>>& g, T v, void (*func) (T, Args...), Args&... args) {
    std::queue<T> q;
    std::vector<bool> visited(g.size());
    q.push(v);
    while (!q.empty()) {
        int p = q.front();
        q.pop();
        visited[p] = true;
        func(p, args...);
        for (int i = 0; i < g.size(); i++) {
            if (g[p][i] && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

template<typename T, typename... Args>
void bfs_list(std::vector<std::vector<T>>& g, T v, void (*func) (T, Args...), Args&... args) {
    std::queue<T> q;
    std::vector<bool> visited(g.size());
    q.push(v);
    while (!q.empty()) {
        int p = q.front();
        q.pop();
        visited[p] = true;
        func(p, args...);
        for (int i = 0; i < g[p].size(); i++) {
            if (!visited[g[p][i]]) {
                q.push(g[p][i]);
                visited[g[p][i]] = true;
            }
        }
    }
}

#endif //ALGOBASE_BFS_H