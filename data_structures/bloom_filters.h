#pragma once
#include "data_structure.h"

/*
bloom filters :
* check whether an element is in an list, can be wrong when there is, can't be wrong when there isn's, has a great advantage on time and space
* insert O(1)
* contains O(log n)
*/

class bloomFilters {
private:
	//Variables
	int n_sets;
	long long** bit_sets;
	int* set_size;
	long long mod_64 = 0x7F;
	long long div_64 = 6;
public:
	bloomFilters(int bit_set_size[], int size) {
		n_sets = size;
		set_size = bit_set_size;
		bit_sets = new long long* [n_sets];
		for (int i = 0; i < n_sets; i++)
			bit_sets[i] = new long long[set_size[i]];
	}

	void insert(int set_index, long hash) {
		hash = hash % set_size[set_index];
		int block = (int)(hash >> div_64);
		bit_sets[set_index][block] |= (1L << (hash & mod_64));
	}

	void insert(long long hashes[]) {
		for (int i = 0; i < n_sets; i++)
			insert(i, hashes[i]);
	}

	bool contains(long long hashes[], int size) {
		for (int i = 0; i < size; i++) {
			int block = (int)(hashes[i] >> div_64);
			long mask = 1L << (hashes[i] & mod_64);
			if ((bit_sets[i][block] & mask) != mask)
				return false;
		}
		return true;
	}
};