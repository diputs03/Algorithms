#pragma once
#include "data_structure.h"
#include "doubly_linked_list.h"

/*
stack :
* insert_tail/remove_tail O(1)
* peek_tail O(1)
*/

template<typename T>
class stack {
private:
	doublyLinkedList<T> l;
public:
	stack() { l.clear(); }
	void push(T val) { l.insert_tail(val); }
	T pop() { return l.remove_tail(); }
	void size() { return l.size(); }
	void empty() { return l.size() == 0; }
	T peek() {
		T tmp = l.remove_tail();
		l.insert_tail(T);
		return tmp;
	}
};