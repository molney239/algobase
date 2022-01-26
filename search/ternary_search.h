#ifndef ALGOBASE_TERNARY_SEARCH_H
#define ALGOBASE_TERNARY_SEARCH_H

template<typename T1, typename T2>
T1 ternary_search(T1 l, T1 r, T1 precision, T2 (*f) (T1)) {
    T1 mid1, mid2;
    while (r - l > precision * 3) {
        mid1 = l + (r - l) / 3.0;
        mid2 = r - (r - l) / 3.0;
        if (f(mid1) < f(mid2)) l = mid1;
        else r = mid2;
    }
    return r;
}

template<typename T1, typename T2, typename... Args>
T1 ternary_search(T1 l, T1 r, T1 precision, T2 (*f) (T1, Args...), Args... args) {
    T1 mid1, mid2;
    while (r - l > precision) {
        mid1 = l + (r - l) / 3.0;
        mid2 = r - (r - l) / 3.0;
        if (f(mid1, args...) < f(mid2, args...)) l = mid1;
        else r = mid2;
    }
    return r;
}

#endif //ALGOBASE_TERNARY_SEARCH_H