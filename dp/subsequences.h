#ifndef ALGOBASE_SUBSEQUENCES_H
#define ALGOBASE_SUBSEQUENCES_H

#include <algorithm>

template<typename T>
vector<unsigned> lis(vector<T>& v) {
    vector<unsigned> dp(v.size(), 1);
    vector<unsigned> from(v.size());
    for (unsigned i = 0; i < v.size(); i++) from[i] = i;

    unsigned pos = 0;
    for (unsigned i = 1; i < v.size(); i++) {
        for (unsigned j = 0; j < i; j++) {
            if (v[j] < v[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                from[i] = j;
            }
        }

        if (dp[i] > dp[pos]) pos = i;
    }

    vector<unsigned> ans;
    while (true) {
        ans.push_back(pos);

        if (from[pos] == pos) break;
        pos = from[pos];
    }

    std::reverse(ans.begin(), ans.end());

    return ans;
}

#endif //ALGOBASE_SUBSEQUENCES_H