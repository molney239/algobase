#ifndef ALGOBASE_MERGE_SORT_H
#define ALGOBASE_MERGE_SORT_H

#include <algorithm>

template<typename T>
void merge_sort(std::vector<T>& v) {
    if (v.size() > 1) {
        std::vector<T> v1 = std::vector<T>(v.begin(), v.begin() + v.size() / 2);
        merge_sort(v1);
        std::vector<T> v2 = std::vector<T>(v.begin() + v.size() / 2, v.end());
        merge_sort(v2);
        std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin());
    }
}

template<typename T>
void merge_sort(std::vector<T>& v, bool (*comp) (T, T)) {
    if (v.size() > 1) {
        std::vector<T> v1 = std::vector<T>(v.begin(), v.begin() + v.size() / 2);
        merge_sort(v1, comp);
        std::vector<T> v2 = std::vector<T>(v.begin() + v.size() / 2, v.end());
        merge_sort(v2, comp);
        std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin(), comp);
    }
}

#endif //ALGOBASE_MERGE_SORT_H