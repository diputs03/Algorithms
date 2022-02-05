#pragma once
#include "data_structure.h"
#include "doubly_linked_list.h"

/*
queue :
* insert_head/remove_tail O(1)
* peek_tail O(1)
*/

template<typename T>
class queue {
private:
	doublyLinkedList<T> l;
public:
	queue() { l.clear(); }
	void push(T val) { l.insert_tail(val); }
	T pop() { return l.remove_head(); }
	void size() { return l.size(); }
	void empty() { return l.size() != 0; }
	T peek_head() {
		T tmp = l.remove_head;
		l.insert_head(tmp);
		return tmp;
	}
};