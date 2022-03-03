#ifndef ALGOBASE_NUMERICAL_H
#define ALGOBASE_NUMERICAL_H

namespace numerical {

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

    template<typename T>
    bool is_prime(T n) {
        if (n <= 1) return false;
        for (T c = 2; c * c <= n; c++) {
            if (n % c == 0) return false;
        }
        return true;
    }

    template<typename T>
    std::vector<T> factorize(T n) {
        std::vector<T> result;
        for (int c = 2; c * c <= n; c++) {
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
        for (int c = 1; c * c <= n; c++) {
            if (n % c == 0) {
                result.push_back(c);
                if (c * c != n) result.push_back(n / c);
            }
        }

        return result;
    }

    template<typename T>
    int divisors_count(T n) {
        int count = 0;
        for (int c = 1; c * c <= n; c++) {
            if (n % c == 0) count++;
            if (c * c != n) count++;
        }
        return count;
    }

}

#endif //ALGOBASE_NUMERICAL_H