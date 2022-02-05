#pragma once
#include "data_structure.h"
/*
heap :
* insert O(n log n)
* remove O(log n)
* peek O(n)
*/

//this is priority queue too!!!
template<typename T>
class indexedHeap {
private:
	//Variables
	int sz;
	int number_elements;
	int degree_node;
	int* child, parent;
	int* position_map;
	int* inverse_map;
	bool min_heap;

	//Functions
	void sink(int i) {
		for (int j = min_child(i); j != -1; ) {
			swap(i, parent[i]);
			i = parent[i];
			j = min_child(i);
		}
	}

	void swim(int i) {
		while (less(i, parent[i])) {
			swap(i, parent[i]);
			i = parent[i];
		}
	}

	int min_child(int i) {
		int index = -1, from = child[i], to = std::min(sz, from + degree_node);
		for (int j = from; j < to; j++)
			if (less(j, i))
				index = i = j;
		return index;
	}

	void swap(int i, int j) {
		position_map[inverse_map[j]] = i;
		position_map[inverse_map[i]] = j;
		int tmp = inverse_map[i];
		inverse_map[i] = inverse_map[j];
		inverse_map[j] = tmp;
	}

	bool less(T a, T b) {
		return a < b;
	}

	bool less(int i, int j) {
		return values[inverse_map[i]] < values[inverse_map[j]];
	}
public:
	T* values;

	indexedHeap(int degree, int max_size) {
		degree_node = std::max(2, degree);
		number_elements = std::max(degree_node + 1, max_size);
		inverse_map = new int[number_elements];
		position_map = new int[number_elements];
		child = new int[number_elements];
		parent = new int[number_elements];
		values = new T[number_elements];

		for (int i = 0; i < number_elements; i++) {
			parent[i] = (i - 1) / degree_node;
			child[i] = i * degree_node + 1;
			position_map[i] = -1;
			inverse_map[i] = -1;
		}
	}

	int size() {
		return sz;
	}

	bool empty() {
		return sz == 0;
	}

	bool contains(int key) {
		return position_map[key] != -1;
	}

	int peek_min_key_index() {
		return inverse_map[0];
	}

	int poll_min_key_index() {
		int min_key = peek_min_key_index();
		remove(min_key);
		return min_key;
	}

	T peek_min_value() {
		return values[inverse_map[0]];
	}

	T poll_min_value() {
		T min_val = peek_min_value();
		remove(peek_min_key_index());
		return min_val;
	}

	void insert(int key, T value) {
		if (contains(key))
			return;
		if (value == NULL)
			return;
		position_map[key] = sz;
		inverse_map[sz] = key;
		values[key] = value;
		swim(sz++);
	}

	T value_of(int key) {
		if (!contains(key))
			return NULL;
		return values[key];
	}

	T remove(int key) {
		if (!contains(key))
			return NULL;
		int i = position_map[key];
		swap(i, --sz);
		sink(i);
		swim(i);
		T value = values[key];
		values[key] = NULL;
		position_map[key] = -1;
		inverse_map[sz] = -1;
		return value;
	}

	T update(int key, T value) {
		if (!contains(key) || value == NULL)
			return NULL;
		int i = position_map[key];
		T old_value = values[key];
		values[key] = value;
		swim(i);
		sink(i);
		return old_value;
	}

	void decrease(int key, T value) {
		if (!contains(key) || value == NULL)
			return;
		if (less(value, values[key])) {
			values[key] = value;
			swim(position_map[key]);
		}
	}

	void increase(int key, T value) {
		if (!contains(key) || value == NULL)
			return;
		if (less(values[key], value)) {
			values[key] = value;
			sink(position_map[key]);
		}
	}
};