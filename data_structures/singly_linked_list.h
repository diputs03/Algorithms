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
class singlyLinkedList {
private:
	struct node {
		int data;
		node* next;
		node() {
			data = NULL;
			next = nullptr;
		}
	};
	int s;
	node* head;
	node* tail;
public:
	singlyLinkedList() {
		s = 0;
		head = nullptr;
		tail = nullptr;
	}

	void clear() {
		node* current = head;
		node* previous;
		s = 0;
		while (current->next != nullptr) {
			previous = current;
			current = current->next;
			delete previous;
		}
	}

	int size() {
		return this->s;
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
		s++;
	}

	void insert_at(int position, T value) {
		node* previousNode = nullptr;
		node* currentNode;
		node* temp = new node;

		currentNode = head;
		for (int i = 0; i < position; i++) {
			previousNode = currentNode;
			currentNode = currentNode->next;
		}

		temp->data = value;
		previousNode->next = temp;
		temp->next = currentNode;
		s++;
	}

	T remove_head() {
		node* temp;
		temp = head;

		head = head->next;
		T tmp = temp->data;
		delete temp;
		s--;
		return tmp;
	}

	T remove_tail() {
		node* current;
		node* previous = nullptr;

		current = head;

		while (current->next != nullptr) {
			previous = current;
			current = current->next;
		}

		tail = previous;
		previous->next = nullptr;
		T tmp = current->data;
		delete current;
		s--;
		return tmp;
	}

	T remove_at(int position) {
		node* current;
		node* previous = nullptr;

		current = head;
		for (int i = 0; i < position; i++) {
			previous = current;
			current = current->next;
		}
		previous->next = current->next;
		T tmp = current->data;
		delete current;
		s--;
		return tmp;
	}

	T peek(int pos) {
		node* current;

		current = head;
		for (int i = 0; i < pos; i++)
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