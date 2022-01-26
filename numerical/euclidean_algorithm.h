#ifndef ALGOBASE_EUCLIDEAN_ALGORITHM_H
#define ALGOBASE_EUCLIDEAN_ALGORITHM_H

template<typename T>
T gcd(T a, T b) {
    if (a < b) std::swap(a, b);
    if (b == 0) return a;
    return gcd(b, a % b);
}

template<typename T>
T lcm(T a, T b) {
    return (a * b) / gcd(a, b);
}

template<typename T>
T extended_gcd (T a, T b, T& x, T& y) {
    bool flag = false;
    if (a < b) {
        std::swap(a, b);
        flag = true;
    }
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = extended_gcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - y1 * (T)(a / b);
    if (flag) std::swap(x, y);
    return d;
}

#endif //ALGOBASE_EUCLIDEAN_ALGORITHM_H