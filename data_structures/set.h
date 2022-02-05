#pragma once
#include "data_structure.h"
#include "hash_table.h"

template<typename T>
class set {
private:
	static const int DUMMY = new int();
	static const int default_capacity = 3;
	static const double default_load_factor = 0.75f;
	hashTable<T, int>* map;

public:
	set(int capacit, double load) {
		map = new hashTable<T, int>(capacit, load);
	}

	void clear() {
		map->clear();
	}

	bool empty() {
		return map->empty();
	}

	bool insert(T elem) {
		return map->insert(elem, DUMMY) == DUMMY;
	}

	bool remove(T elem) {
		return map->remove_key(elem);
	}

	bool contains(T elem) {
		return map->contains_key(elem);
	}
};