#ifndef ALGOBASE_INSERTION_SORT_H
#define ALGOBASE_INSERTION_SORT_H

template<typename T>
void insertion_sort(std::vector<T>& v) {
    size_t sz = v.size();
    for (unsigned long long i = 1; i < sz; i++) {
        unsigned long long pos = i;
        while (pos > 0 && v[pos] < v[pos - 1]) {
            swap(v[pos - 1], v[pos]);
            pos--;
        }
    }
}

template<typename T>
void insertion_sort(std::vector<T>& v, bool (*comp) (T, T)) {
    size_t sz = v.size();
    for (unsigned long long i = 1; i < sz; i++) {
        unsigned long long pos = i;
        while (pos > 0 && comp(v[pos], v[pos - 1])) {
            swap(v[pos - 1], v[pos]);
            pos--;
        }
    }
}

#endif //ALGOBASE_INSERTION_SORT_H
