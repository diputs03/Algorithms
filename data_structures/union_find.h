#pragma once
#include "data_structure.h"


class unionFind {
private:
	int s;
	int* sz;
	int* id;
	int number_components;
public:
	unionFind(int sze) {
		s = sze;
		number_components = sze;
		sz = new int[s];
		id = new int[s];

		for (int i = 0; i < s; i++)
			id[i] = i, sz[i] = 1;
	}

	int find(int p) {
		if (p == id[p])
			return p;
		return id[p] = find(id[p]);
	}

	bool connected(int p, int q) {
		return find(p) == find(q);
	}

	int component_size(int p) {
		return sz[find(p)];
	}

	int size(int k) {
		return sz[find(k)];
	}

	int components() {
		return number_components;
	}

	void unify(int p, int q) {
		int root1 = find(p);
		int root2 = find(q);

		if (root1 == root2)
			return;

		if (sz[root1] < sz[root2]) {
			sz[root2] += sz[root1];
			id[root1] = root2;
		}
		else {
			sz[root1] += sz[root2];
			id[root2] = root1;
		}
		number_components--;
	}

	int* list(int k) {
		int* ret = new int[sz[k]];
		for (int i = 0, j = 0; i < n; i++)
			if (id[i] == k)
				ret[j++] = i;
		return ret;
	}
};