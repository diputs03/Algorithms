#pragma once
#include "data_structure.h"

/*
dinamic array :
* insert/remove O(n)
* peek O(1)
* contains O(1)
*/

template<typename T>
class dinamicArray {
private:
	//Variables
	T* arr;
	int length;
	int capacity;
public:
	dinamicArray() {
		this->length = 0;
		this->capacity = 0;
	}
	dinamicArray(int c) {
		this->capacity = c;
		this->length = 0;
		arr = new T[capacity];
	}

	int size() {
		return this->length;
	}

	bool empty() {
		return this->size() == 0;
	}

	T operator[](int index) {
		return this->arr[index];
	}

	void set(int index, T element) {
		this->arr[index] = element;
	}

	void clear() {
		delete[]arr;
		this->length = 0;
		this->capacity = 0;
	}

	void resize(int size) {
		this->capacity = size;
		T* new_arr = new T[this->capacity];
		for (int i = 0; i < this->length; i++)
			new_arr[i] = this->arr[i];
		delete[] arr;
		this->arr = new_arr;
	}

	void insert(T element) {
		if (this->length + 1 >= this->capacity)
			resize(this->capacity * 2);
		this->arr[this->length++] = element;
	}

	T remove_at(int remove_index) {
		T data = this->arr[remove_index];
		T* new_arr = new T[this->length];
		for (int i = 0, j = 0; i < this->length; i++, j++)
			if (i == remove_index) j--;
			else new_arr[j] = this->arr[i];
		delete[] arr;
		this->arr = new_arr;
		this->capacity = --this->length;
		return data;
	}

	bool remove(T obj) {
		for (int i = 0; i < this->length; i++)
			if (this->arr[i] == obj) {
				remove_at(i);
				return true;
			}
		return false;
	}

	int index_of(T obj) {
		for (int i = 0; i < this->length; i++)
			if (this->arr[i] == obj)
				return i;
		return -1;
	}

	bool contains(T obj) {
		return index_of(obj) != -1;
	}

	//print the array
	void print() {
		for (int i = 0; i < size(); i++)
			std::cout << arr[i] << " ";
		std::cout << std::endl;
	}
};
