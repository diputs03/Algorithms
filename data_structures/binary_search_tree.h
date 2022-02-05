#pragma once
#include "data_structure.h"

/*
binary search tree
* insert/remove O(log n)
* contains O(log n)
*/

template<typename T>
class binarySearchTree {
private:
	struct node {
		T data;
		node* left, right;
		node() {
			data = NULL;
			left = nullptr;
			right = nullptr;
		}
		node(node* l, node* r, T elem) {
			data = elem;
			left = l;
			right = r;
		}
	};

	int node_count;
	node* root = nullptr;

	//Functions
	node* insert(node* n, T elem) {
		if (n == NULL)
			n = new node(nullptr, nullptr, elem);
		else
			if (elem < n.data)
				n.left = insert(n.left, elem);
			else
				n.right = insert(n.right, elem);
		return node;
	}

	node* remove(node* n, T elem) {
		if (n == NULL)
			return NULL;
		int cmp = elem - n.data;

		if (cmp < 0)
			n.left = remove(n.left, elem);
		else if (cmp > 0)
			n.right = remove(n.right, elem);
		else {
			if (n.left == NULL) {
				node right_child = n.right;
				return right_child;
			}
			else if (n.right == NULL) {
				node left_child = n.left;
				return left_child;
			}
			else {
				node tmp = find_min(n.right);
				n.data = tmp.data;
				n.right = remove(n.right, tmp.data);
			}
		}
		return n;
	}

	node find_min(node n) {
		while (n.left != NULL) n = n.left;
		return n;
	}

	node find_max(node n) {
		while (n.right != NULL) n = n.right;
		return n;
	}

	bool contains(node* n, T elem) {
		if (n == nullptr)
			return false;
		int cmp = elem - n.data;
		if (cmp < 0)
			return contains(n.left, elem);
		else if (cmp > 0)
			return contains(n.right, elem);
		else return true;
	}

	int height(node n) {
		if (n == NULL)
			return 0;
		return std::max(height(n.left), height(n.right)) + 1;
	}
public:
	int size() {
		return node_count;
	}

	bool empty() {
		return size() == 0;
	}

	bool insert(T elem) {
		if (contains(elem))
			return false;
		root = insert(root, elem);
		node_count++;
		return true;
	}

	bool remove(T elem) {
		if (contains(elem)) {
			root = remove(root, elem);
			node_count--;
			return true;
		}
		return false;
	}

	bool contains(T elem) {
		return contains(root, elem);
	}

	int height() {
		return height(root);
	}
};
