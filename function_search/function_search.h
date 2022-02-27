#ifndef ALGOBASE_FUNCTION_SEARCH_H
#define ALGOBASE_FUNCTION_SEARCH_H

namespace function_search {

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

}

#endif //ALGOBASE_FUNCTION_SEARCH_H