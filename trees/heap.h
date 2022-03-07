#ifndef ALGOBASE_HEAP_H
#define ALGOBASE_HEAP_H

#include <vector>

namespace binary_heap {

    template<typename T>
    bool less(T x, T y) {
        return x < y;
    }

    template<typename T>
    void shift_up(std::vector<T>& v, unsigned pos, bool (*comp) (T, T) = less) {
        while (pos > 0 && comp(v[pos], v[(pos - 1) / 2])) {
            swap(v[(pos - 1) / 2], v[pos]);
            pos = (pos - 1) / 2;
        }
    }

    template<typename T>
    void shift_down(std::vector<T>& v, unsigned pos, bool (*comp) (T, T) = less) {
        while (pos * 2 + 1 < v.size()) {
            unsigned u = pos * 2 + 1;
            if (pos * 2 + 2 < v.size() && comp(v[pos * 2 + 2], v[pos * 2 + 1])) u = pos * 2 + 2;
            if (comp(v[pos], v[u])) break;

            swap(v[pos], v[u]);
            pos = u;
        }
    }

    template<typename T>
    void build(std::vector<T>& v, bool (*comp) (T, T) = less) {
        for (int i = v.size(); i >= 0; i--) {
            shift_down(v, i, comp);
        }
    }

    template<typename T>
    void insert(std::vector<T>& v, T value, bool (*comp) (T, T) = less) {
        v.push_back(value);
        shift_up(v, v.size() - 1, comp);
    }

    template<typename T>
    T get(std::vector<T>& v) {
        return v.front();
    }

    template<typename T>
    void pop(std::vector<T>& v, bool (*comp) (T, T) = less) {
        swap(v[0], v.back());
        v.pop_back();
        shift_down(v, 0, comp);
    }

}

#endif //ALGOBASE_HEAP_H