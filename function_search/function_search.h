#ifndef ALGOBASE_FUNCTION_SEARCH_H
#define ALGOBASE_FUNCTION_SEARCH_H

namespace function_search {


    /**
     * Searches least argument in range [l; r] for which function returns true.
     *
     * @tparam T Type of function argument
     * @tparam Args Parameter pack for additional function arguments
     * @param l Left range bound
     * @param r Right range bound
     * @param step Step for search
     * @param good Function for search
     * @param args Additional arguments for function
     * @return Least argument in range [l; r] for which function returns true
     */
    template<typename T, typename... Args>
    T linear_search(T l, T r, T step, bool (*good) (T, Args...), Args... args) {
        T pos = l;
        while (pos < r) {
            if (good(pos, args...)) return pos;
            pos += step;
        }
        return r;
    }


    /**
     * Searches least argument in range [l; r] for which monotonically increasing function returns true.
     *
     * @tparam T Type of function argument
     * @tparam Args Parameter pack for additional function arguments
     * @param l Left range bound
     * @param r Right range bound
     * @param precision Precision for binary search bounds
     * @param good Monotonically increasing function for search
     * @param args Additional arguments for function
     * @return Least argument in range [l; r] for which function returns true
     */
    template<typename T, typename... Args>
    T binary_search(T l, T r, T precision, bool (*good) (T, Args...), Args... args) {
        T mid;
        while (r - l > precision) {
            mid = l + (r - l) / 2;
            if (good(mid, args...)) r = mid;
            else l = mid + 1;
        }
        return r;
    }


    /**
     * Searches for the function argument for which it reaches its minimum on range [l; r].
     * The function must first be monotonically decreasing and then monotonically increasing.
     *
     * @tparam T1 Type of function argument
     * @tparam T2 Function return type
     * @tparam Args Parameter pack for additional function arguments
     * @param l Left range bound
     * @param r Right range bound
     * @param precision Precision for ternary search bounds
     * @param func Function for search
     * @param args Additional arguments for function
     * @return Function argument at which it reaches its minimum
     */
    template<typename T1, typename T2, typename... Args>
    T1 ternary_search(T1 l, T1 r, T1 precision, T2 (*func) (T1, Args...), Args... args) {
        T1 mid1, mid2;
        while (r - l > precision) {
            mid1 = l + (r - l) / 3.0;
            mid2 = r - (r - l) / 3.0;
            if (func(mid1, args...) < func(mid2, args...)) l = mid1;
            else r = mid2;
        }
        return r;
    }

}

#endif //ALGOBASE_FUNCTION_SEARCH_H