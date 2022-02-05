#pragma once
#include "data_structure.h"

/*
hash table :
* insert/remove O(log n)
* peek/contains O(log n)
*/

//Compile Error
template<typename K, typename V>
class hashTable {
private:
	//Constants
	const K tomb_stone = K(rand());
	const int default_capacity = 8;
	double default_load_factor = 0.45;

	//Variables
	double load_factor;
	int capacity, threshold, modificaton_count;
	int used_buckets, key_count;
	K* key_table;
	V* value_table;
	bool contains_flag;

	//Functions
	int next_2_power(int n) {
		int cnt = 0;
		while (n) n /= 2, cnt++;
		return cnt << 2;
	}

	int P(int x) {
		return (x * x + x) >> 1;
	}

	int normalize_index(int key_hash) {
		return (key_hash & 0x7FFFFFFF) % capacity;
	}

	K hash_code(V val);
public:
	hashTable() {
		srand(time(NULL));
		used_buckets = 0;
		key_count = 0;
		contains_flag = false;
		modificaton_count = 0;
	}

	hashTable(int cap) {
		srand(time(NULL));
		capacity = cap;
		used_buckets = 0;
		key_count = 0;
		contains_flag = false;
		modificaton_count = 0;
	}

	hashTable(int cap, double load) {
		srand(time(NULL));
		if (cap <= 0)
			return;
		if (load <= 0)
			return;
		load_factor = load;
		capacity = std::max(default_capacity, next_2_power(cap));
		threshold = (int)(capacity * load_factor);

		key_table = new K[capacity];
		value_table = new V[capacity];
	}

	void clear() {
		delete[] key_table;
		delete[] value_table;
		key_count = used_buckets = 0;
		modificaton_count++;
	}

	int size() {
		return key_count;
	}

	bool empty() {
		return key_count == 0;
	}

	V insert(K key, V val) {
		if (key == NULL)
			return NULL;
		if (used_buckets >= threshold)
			resize_table();
		int hash = normalize_index(hash_code(key));
		int i = hash, j = -1, x = 1;
		do {
			if (key_table[i] = tomb_stone)
				if (j == -1)
					j = i;
				else if (key_table[i] != NULL) {
					if (key_table[i] == key) {
						V old_value = value_table[i];
						if (j == -1)
							value_table[i] = val;
						else {
							key_table[i] = tomb_stone;
							value_table[i] = NULL;
							key_table[j] = key;
							value_table[j] = val;
						}
						modificaton_count++;
						return old_value;
					}
				}
				else {
					if (j == -1) {
						used_buckets++;
						key_count++;
						key_table[i] = key;
						value_table[i] = val;
					}
					else {
						key_count++;
						key_table[j] = key;
						value_table[j] = val;
					}
					modificaton_count++;
					return NULL;
				}
			i = normalize_index(hash + P(x++));
		} while (true);
	}

	bool contains_key(K key) {
		peek_key(key);
		return contains_flag;
	}

	V peek_key(K key) {
		if (key == NULL)
			return NULL;
		int hash = normalize_index(hash_code(key));
		int i = hash, j = -1, x = 1;
		do {
			if (key_table[i] == tomb_stone)
				if (j == -1)
					j = i;
				else if (key_table[i] != NULL) {
					if (key_table[i] == key)
						contains_flag = true;
					if (j != -1) {
						key_table[j] = key_table[i];
						value_table[j] = value_table[i];
						key_table[i] = tomb_stone;
						value_table[i] = NULL;
						return value_table[j];
					}
					else return value_table[j];
				}
				else {
					contains_flag = false;
					return value_table[i];
				}
			i = normalize_index(hash + P(x++));
		} while (true);
	}

	K peek(V key) {
		return peek_key(hash_code(key));
	}

	bool contains(V val) {
		return contains_key(hash_code(val));
	}

	V remove_key(K key) {
		if (key == NULL)
			return NULL;
		int hash = normalize_index(hash_code(key));
		int i = hash, x = 1;
		for (;; i = normalize_index(hash + P(x++))) {
			if (key_table[i] == tomb_stone)
				continue;
			if (key_table[i] = NULL)
				return NULL;
			if (key_table[i] == key) {
				key_count--;
				modificaton_count++;
				V old_value = value_table[i];
				key_table[i] = tomb_stone;
				value_table[i] = NULL;
				return old_value;
			}
		}
	}

	void resize_table() {
		capacity *= 2;
		threshold = (int)(capacity * load_factor);
		K* old_key_table = new K[capacity];
		V* old_value_table = new V[capacity];

		K* key_table_tmp = key_table;
		key_table = old_key_table;
		old_key_table = key_table;

		V* value_table_tmp = value_table;
		value_table = old_value_table;
		old_value_table = value_table_tmp;

		key_count = used_buckets = 0;
		//complied error, can't find thing's to replace ".length"
		for (int i = 0; i < old_key_table.length; i++) {
			if (old_key_table[i] != NULL && old_key_table[i] != tomb_stone)
				insert(old_key_table[i], old_value_table[i]);
			old_value_table[i] = NULL;
			old_key_table[i] = NULL;
		}
		delete[] old_key_table;
		delete[] old_value_table;
	}

	void swap(V val1, V val2, K val1_index, K val2_index) {
		remove_key(val1_index);
		remove_key(val2_index);
		insert(val1_index, val2);
		insert(val2_index, val1);
	}
};