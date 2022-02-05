#pragma once
#include "data_structure.h"

/*
linked list :
* insert/remove :
* * head O(1)
* * tail O(1)
* * mid O(n)
* peek O(n)
*/

template<typename T>
class doublyLinkedList {
private:
	struct node {
		T data;
		node* next;
		node* last;
		node() {
			data = NULL;
			next = nullptr;
			last = nullptr;
		}
	};
	int s;
	node* head;
	node* tail;
public:
	doublyLinkedList() {
		s = 0;
		head = NULL;
		tail = NULL;
	}

	void clear() {
		node* current = head;
		while (current->next != nullptr) {
			current = current->next;
			delete current->last;
		}
	}

	int size() {
		return this->size;
	}

	bool empty() {
		return s == 0;
	}

	void insert_tail(T value) {
		node* temp = new node;
		temp->data = value;
		if (this->empty()) {
			head = temp;
			tail = temp;
		}
		else {
			tail->next = temp;
			temp->last = tail;
			tail = temp;
		}
		s++;
	}

	void insert_head(T value) {
		node* temp = new node;
		temp->data = value;
		temp->next = head;
		head = temp;
		if (this->empty())
			this->tail = temp;
		else head->last = temp;
		s++;
	}

	void insert_at(int position, T value) {
		node* currentNode;
		node* temp = new node;

		currentNode = head;
		for (int i = 0; i < position - 1; i++) {
			currentNode = currentNode->next;
		}

		temp->data = value;
		temp->last = currentNode;
		temp->next = currentNode->next;
		currentNode->next = temp;
		temp->next->last = temp;
		s++;
	}

	T remove_head() {
		node* temp;
		temp = head;
		T tmp = head->data;
		head->next->next->last = head;
		head = head->next;
		delete temp;
		s--;
		return tmp;
	}

	T remove_tail() {
		node* current;

		current = head;

		while (current->next != nullptr) {
			current = current->next;
		}

		T tmp = current->data;
		tail = current->last;
		current->last->next = nullptr;
		delete current;
		s--;
		return tmp;
	}

	T remove_at(int position) {
		node* current;

		current = head;
		for (int i = 0; i < position; i++) {
			current = current->next;
		}
		T tmp = current->data;
		current->last->next = current->next;
		current->next->last = current->last;
		delete current;
		s--;
		return tmp;
	}

	T peek(int pos) {
		node* current;
		current = head;
		for (int i = 0; i < pos - 1; i++)
			current = current->next;
		return current->data;
	}

	void set(int pos, T val) {
		node* current;

		current = head;
		for (int i = 0; i < pos; i++)
			current = current->next;
		current->data = val;
	}

	//print the list
	void print() {
		node* trav = head;
		for (int i = 0; i < s; i++)
			std::cout << trav->data << " ", trav = trav->next;
		std::cout << std::endl;
	}
};