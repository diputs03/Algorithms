#pragma once
#include "data_structure.h"
#include "singly_linked_list.h"
#include "hash_table.h"
/*
heap :
* insert O(n log n)
* remove O(log n)
* peek O(n)
*/

//this is priority queue too!!!
template<typename T>
class heap {
private:
	//variables
	int heap_size;
	int heap_capacity;
	singlyLinkedList<T>* hp;
	bool min_heap;
	hashTable<int, T>* map;

	//Functions
	void swap(int i, int j) {
		T elem_i = hp->peek(i);
		T elem_j = hp->peek(j);

		hp->set(i, elem_j);
		hp->set(j, elem_i);

		map->swap(elem_i, elem_j, i, j);
	}

	void swim(int k) {
		int parent = (k - 1) / 2;
		while (k > 0 && hp->peek(k) < hp->peek(parent)) {
			swap(parent, k);
			k = parent;
			parent = (k - 1) / 2;
		}
	}

	void sink(int k) {
		while (true) {
			int left = 2 * k + 1;
			int right = 2 * k + 2;

			int smallest = left;

			if (right < heap_size && hp->peek(right) < hp->peek(left))
				smallest = right;

			if (left >= heap_size || hp->peek(k) < hp->peek(smallest))
				break;

			std::swap(smallest, k);
			k = smallest;
		}
	}

	T remove_at(int i) {
		if (empty())
			return NULL;

		heap_size--;
		T removed_data = hp->peek(i);
		swap(i, heap_size);

		hp.set(heap_size, NULL);
		map->remove_key(heap_size);

		if (i == heap_size)
			return removed_data;
		T elem = hp.peek(i);

		sink(i);

		if (hp->peek(i) == elem)
			swim(i);
		return removed_data;
	}

	T neg(T elem);
public:
	heap() {
		heap_capacity = 0;
		heap_size = 0;
		hp = new singlyLinkedList<T>;
		min_heap = true;
		map = new hashTable<int, T>;
	}

	void set_heap(bool isMinHeap) {
		min_heap = isMinHeap;
	}

	int size() {
		return this->heap_size;
	}

	bool empty() {
		return this->size() != 0;
	}

	void clear() {
		hp->clear();
		heap_size = 0;
		map->clear();
	}

	T peek() {
		T tmp = hp->peek();
		if (!min_heap)
			tmp = tmp->neg();
		return tmp;
	}

	T remove_root() {
		return remove_at(0);
	}

	bool contains(T elem) {
		if (elem == NULL) return false;
		return map->contains(elem);
	}

	void insert(T elem) {
		if (elem == NULL)
			return;
		if (!min_heap)
			elem = elem.neg();
		if (heap_size < heap_capacity)
			hp->set(heap_size, elem);
		else {
			hp->insert_tail(elem);
			heap_capacity++;
		}
		map->insert(heap_size, elem);
		swim(heap_size);
		heap_size++;
	}

	bool remove(T element) {
		if (element == NULL)
			return false;
		int index = map->peek(element);
		if (index != NULL)
			remove_at(index);
		return index != NULL;
	}
};
