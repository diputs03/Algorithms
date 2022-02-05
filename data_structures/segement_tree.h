#pragma once
#include "data_structure.h"

class segementTree {
private:
	int N;
	long long U = 8123572096793136074L;
	long long* tree;
public:
	segementTree(int size) {
		tree = new long long[2 * (N = size)];
		memset(tree, U, sizeof(long long) * 2 * size);
	}

	segementTree(long long values[], int size) {
		tree = new long long[2 * (N = size)];
		memset(tree, U, sizeof(long long) * 2 * size);
		for (int i = 0; i < N; i++)
			modify(i, values[i]);
	}

	//this function is used for queries
	long long function(long long a, long long b);

	void modify(int i, long long value) {
		tree[i + N] = function(tree[i + N], value);
		for (i += N; i > 1; i >>= 1)
			tree[i >> 1] = function(tree[i], tree[i ^ 1]);
	}

	long long query(int l, int r) {
		long long res = U;
		for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
			if (l & 1)
				res = function(res, tree[l++]);
			if (r & 1)
				res = function(res, tree[--r]);
		}
		return res;
	}
};