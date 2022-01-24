#ifndef ALGOBASE_SELECTION_SORT_H
#define ALGOBASE_SELECTION_SORT_H

template<typename T>
void selection_sort(std::vector<T>& v) {
    size_t sz = v.size();
    for (unsigned long long i = 0; i < sz; i++) {
        unsigned long long  mn = i;
        for (unsigned long long j = i + 1; j < sz; j++) {
            if (v[j] < v[mn]) mn = j;
        }
        std::swap(v[i], v[mn]);
    }
}

template<typename T>
void selection_sort(std::vector<T>& v, bool (*comp) (T, T)) {
    size_t sz = v.size();
    for (unsigned long long i = 0; i < sz; i++) {
        unsigned long long  mn = i;
        for (unsigned long long j = i + 1; j < sz; j++) {
            if (comp(v[j], v[mn])) mn = j;
        }
        std::swap(v[i], v[mn]);
    }
}

#endif //ALGOBASE_SELECTION_SORT_H
