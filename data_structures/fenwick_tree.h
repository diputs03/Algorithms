#pragma once
#include "data_structure.h"

/*
FenwickTree
* sum O(log n)
*/

//Fenwick Trees are always one based
template<typename T>
class FenwickTree {
private:
	//Variables
	T* tree;
	int length;

	//Functions
	int lsb(int i) {
		return i & -i;
	}
public:
	FenwickTree(int sz) {
		tree = new T[sz];
		length = sz;
	}

	FenwickTree(long long val[], int sz) {
		if (val == NULL)
			return;
		tree = new T[sz];
		for (int i = 0; i < sz; i++)
			tree[i] = val[i];
		length = sz;
		for (int i = 1; i < length; i++) {
			int j = i + lsb(i);
			if (j < length)
				tree[j] += tree[i];
		}
	}

	T prefix_sum(int i) {
		T sum = 0;
		while (i != 0) {
			sum += tree[i];
			i &= ~lsb(i);
		}
		return sum;
	}

	T sum(int i, int j) {
		return prefix_sum(j) - prefix_sum(i);
	}

	void add(int i, T k) {
		while (i < length) {
			tree[i] += k;
			i += lsb;
		}
	}

	void set(int i, T k) {
		T val = sum(i, i);
		add(i, k - val);
	}
};