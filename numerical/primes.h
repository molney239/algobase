#ifndef ALGOBASE_PRIMES_H
#define ALGOBASE_PRIMES_H

#include <cmath>
#include <vector>

template<typename T>
bool is_prime(T n) {
    if (n <= 1) return false;
    for (T c = 2; c <= floor(sqrt(n)); c++) {
        if (n % c == 0) return false;
    }
    return true;
}

template<typename T>
std::vector<T> factorize(T n) {
    std::vector<T> result;
    for (int c = 2; c <= floor(sqrt(n)); c++) {
        while (n % c == 0) {
            n /= c;
            result.push_back(c);
        }
    }
    if (n != 1) result.push_back(n);

    if (result.empty()) result.push_back(1);
    return result;
}

template<typename T>
std::vector<T> divisors(T n) {
    std::vector<T> result;
    for (int c = 1; c <= floor(sqrt(n)); c++) {
        if (n % c == 0) {
            result.push_back(c);
            if (c * c != n) result.push_back(n / c);
        }
    }

    return result;
}

template<typename T>
std::vector<T> ordered_divisors(T n) {
    std::vector<T> result;
    for (int c = 1; c <= n; c++) {
        if (n % c == 0) result.push_back(c);
    }

    return result;
}

template<typename T>
int divisors_count(T n) {
    int count = 0;
    for (int c = 1; c <= floor(sqrt(n)); c++) {
        if (n % c == 0) count++;
        if (c * c != n) count++;
    }
    return count;
}

#endif //ALGOBASE_PRIMES_H