#ifndef ALGOBASE_DFS_H
#define ALGOBASE_DFS_H

#include <vector>

template<typename T, typename... Args>
void dfs_matrix(std::vector<std::vector<T>>& g, std::vector<char>& visited, T v,
                void (*func) (T, Args...), Args&... args) {
    visited[v] = 1;
    func(v, args...);
    for (int i = 0; i < g[v].size(); i++) {
        if (g[v][i] && !visited[i]) dfs_matrix(g, visited, i, func, args...);
    }
    visited[v] = 2;
}

template<typename T, typename... Args>
void dfs_list(std::vector<std::vector<T>>& g, std::vector<char>& visited, T v,
                void (*func) (T, Args...), Args&... args) {
    visited[v] = 1;
    func(v, args...);
    for (int i = 0; i < g[v].size(); i++) {
        if (!visited[g[v][i]]) dfs_list(g, visited, g[v][i], func, args...);
    }
    visited[v] = 2;
}

#endif //ALGOBASE_DFS_H