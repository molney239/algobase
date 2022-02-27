#ifndef ALGOBASE_SORTS_H
#define ALGOBASE_SORTS_H

namespace sorts {

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

    // Quick sort

    // Radix sort

}

#endif //ALGOBASE_SORTS_H