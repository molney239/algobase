#ifndef ALGOBASE_LINEAR_SEARCH_H
#define ALGOBASE_LINEAR_SEARCH_H

template<typename T>
T linear_search(T l, T r, T step, bool (*good) (T)) {
    T pos = l;
    while (pos < r) {
        if (good(pos)) return pos;
        pos += step;
    }
    return r;
}

template<typename T, typename... Args>
T linear_search(T l, T r, T step, bool (*good) (T, Args...), Args... args) {
    T pos = l;
    while (pos < r) {
        if (good(pos, args...)) return pos;
        pos += step;
    }
    return r;
}

#endif //ALGOBASE_LINEAR_SEARCH_H