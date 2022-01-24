#ifndef ALGOBASE_HEAP_SORT_H
#define ALGOBASE_HEAP_SORT_H

#include <algorithm>

template<typename T>
void heap_sort(std::vector<T>& v) {
    std::make_heap(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) std::pop_heap(v.begin(), v.end() - i);
}

template<typename T>
void heap_sort(std::vector<T>& v, bool (*comp) (T, T)) {
    std::make_heap(v.begin(), v.end(), comp);
    for (int i = 0; i < v.size(); i++) std::pop_heap(v.begin(), v.end() - i, comp);
}

#endif //ALGOBASE_HEAP_SORT_H