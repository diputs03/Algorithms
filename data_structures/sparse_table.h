#pragma once
#include "data_structure.h"
class MinSparseTable {

    // The number of elements in the original input array.
private:
    int n;
    int P;
    int* log2;
    long long** dp;
    int** it;

public:
    MinSparseTable(long long* values, int length) {
        init(values, length);
    }

private:
    void init(long long* v, int length) {
        n = length;
        P = (int)(std::log(n) / std::log(2));
        dp = new long long*[P + 1];
        for (int i = 0; i < P + 1; i++)
            dp[i] = new long long[n];
        it = new int*[P + 1];
        for (int i = 0; i < P + 1; i++)
            it[i] = new int[n];

        for (int i = 0; i < n; i++) {
            dp[0][i] = v[i];
            it[0][i] = i;
        }

        log2 = new int[n + 1];
        for (int i = 2; i <= n; i++) {
            log2[i] = log2[i / 2] + 1;
        }

        for (int p = 1; p <= P; p++) {
            for (int i = 0; i + (1 << p) <= n; i++) {
                long leftInterval = dp[p - 1][i];
                long rightInterval = dp[p - 1][i + (1 << (p - 1))];
                dp[p][i] = std::min(leftInterval, rightInterval);

                if (leftInterval <= rightInterval) {
                    it[p][i] = it[p - 1][i];
                }
                else {
                    it[p][i] = it[p - 1][i + (1 << (p - 1))];
                }
            }
        }
    }

public:
    int queryIndex(int l, int r) {
        int len = r - l + 1;
        int p = log2[r - l + 1];
        long leftInterval = dp[p][l];
        long rightInterval = dp[p][r - (1 << p) + 1];
        if (leftInterval <= rightInterval)
            return it[p][l];
        else
            return it[p][r - (1 << p) + 1];
    }
};