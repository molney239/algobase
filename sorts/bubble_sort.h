#ifndef ALGOBASE_BUBBLE_SORT_H
#define ALGOBASE_BUBBLE_SORT_H

template<typename T>
void bubble_sort(std::vector<T>& v) {
    size_t sz = v.size();
    for (unsigned long long i = 0; i < sz; i++) {
        bool swapped = false;
        for (unsigned long long j = 1; j < sz; j++) {
            if (v[j] < v[j - 1]) {
                swap(v[j - 1], v[j]);
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

template<typename T>
void bubble_sort(std::vector<T>& v, bool (*comp) (T, T)) {
    size_t sz = v.size();
    for (unsigned long long i = 0; i < sz; i++) {
        bool swapped = false;
        for (unsigned long long j = 1; j < sz; j++) {
            if (comp(v[j], v[j - 1])) {
                swap(v[j - 1], v[j]);
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

#endif //ALGOBASE_BUBBLE_SORT_H