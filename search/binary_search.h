#ifndef ALGOBASE_BINARY_SEARCH_H
#define ALGOBASE_BINARY_SEARCH_H

#include <iostream>

template<typename T>
T binary_search(T l, T r, T precision, bool (*good) (T)) {
    T mid;
    while (r - l > precision) {
        mid = l + (r - l) / 2;
        if (good(mid)) r = mid;
        else l = mid + 1;
    }
    return r;
}

template<typename T, typename... Args>
T binary_search(T l, T r, T precision, bool (*good) (T, Args...), Args... args) {
    T mid;
    while (r - l > precision) {
        mid = l + (r - l) / 2;
        if (good(mid, args...)) r = mid;
        else l = mid + 1;
    }
    return r;
}

#endif //ALGOBASE_BINARY_SEARCH_H