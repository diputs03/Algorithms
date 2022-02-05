#pragma once
#include "data_structure.h"

/*
* balanced tree
* insert/remove O(log n)
*/

template<typename T>
class AVLTree {
private:
	//Classes
	class node {
	public:
		int balance_factor;
		T value;
		int height;
		node* right, left;
		node(T val) {
			balance_factor = 0;
			height = 0;
			value = val;
			right = nullptr;
			left = nullptr;
		}

		node() {
			balance_factor = 0;
			height = 0;
			value = NULL;
			right = nullptr;
			left = nullptr;
		}
	};

	//Variables
	node* root;

	int node_count;

	//Functions
	bool contains(node* n, T val) {
		if (*n == NULL)
			return false;
		int cmp = val - n->value;
		if (cmp < 0)
			return contains(n->left, val);
		if (cmp > 0)
			return contain(n->right, val);
		return true;
	}

	node insert(node* n, T val) {
		if (*n == NULL)
			return new node(val);

		int cmp = val - n.value;

		if (cmp < 0)
			n->left = insert(n->left, val);
		else
			n->right = insert(n->right, val);
		update(n);
		return balance(n);
	}

	void update(node* n) {
		int left_node_height = (n->left == nullptr) ? -1 : n->left->height;
		int right_node_height = (n->right == nullptr) ? -1 : n->right->height;
		n->height = 1 + max(left_node_height, right_node_height);
		n->balance_factor = right_node_height - left_node_height;
	}

	node balance(node* n) {
		if (n->balance_factor == -2)
			if (n->left->balance_factor <= 0)
				return left_left_case(n);
			else
				return left_right_case(n);
		else if (n->balance_factor == 2)
			if (n->right->balance_fatcor >= 0)
				return right_right_case(n);
			else
				return right_left_case(n);
		else
			return n;
	}

	node left_left_case(node* n) {
		return right_rotation(n);
	}
	node left_right_case(node* n) {
		n->left = left_rotation(n->left);
		return left_left_case(n);
	}
	node right_right_case(node* n) {
		return left_rotation(n);
	}
	node right_left_case(node* n) {
		n->right = right_rotation(n->right);
		return right_right_case(n);
	}

	node left_rotation(node* n) {
		node* new_parent = n->right;
		n->right = new_parent->left;
		new_parent->left = n;
		update(n);
		update(new_parent);
		return new_parent;
	}
	node right_rotation(node* n) {
		node new_parent = n->left;
		n->left = new_parent->right;
		new_parent->right = n;
		update(n);
		update(new_parent);
		return new_parent;
	}

	node remove(node* n, T elem) {
		if (*n == NULL)
			return NULL;
		int cmp = elem - n->value;
		if (cmp < 0)
			n->left = remove(n->left, elem);
		else if (cmp > 0)
			n->right = remove(n->right, elem);
		else {
			if (n->left == nullptr)
				return n->right;
			else if (n->right == nullptr)
				return n->left;
			else {
				if (n->left->height > n->right->height) {
					T successor_val = find_max(n->left);
					n->value = successor_val;
					n->left = remove(n->left, successor_val);
				}
				else {
					T successor_val = find_min(n->right);
					n->value = successor_val;
					n->right = remove(n->right, successor_val);
				}
			}
		}
		update(n);
		return balance(n);
	}

	//n* or n???
	T find_max(node* n) {
		while (n->left != nullptr)
			n = n->left;
		return n->value;
	}
	T find_min(node* n) {
		while (n->right != nullptr)
			n = n->right;
		return n->value;
	}
public:

	int height() {
		if (root == nullptr)
			return 0;
		return (*root).height;
	}

	int size() {
		return node_count;
	}

	bool empty() {
		return node_count == 0;
	}

	bool contains(T val) {
		return contains(root, val);
	}

	bool insert(T val) {
		if (val == NULL)
			return false;
		if (!contains(root, val)) {
			root = insert(root, val);
			node_count++;
			return true;
		}
		return false;
	}

	bool remove(T elem) {
		if (elem == NULL)
			return false;

		if (contains(root, elem)) {
			root = remove(root, elem);
			node_count--;
			return true;
		}
		return false;
	}
};