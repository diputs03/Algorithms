#pragma once
#include "data_structure.h"

/*
* balanced tree
* insert/remove O(log n)
*/

template<typename T>
class redBlackTree {
private:
	//Classes
	class node {
	public:
		bool color;
		T value;
		node* left, right, parent;
		node() {
			color = red;
			value = NULL;
			left = nullptr;
			right = nullptr;
			parent = nullptr;
		}
		node(T val, node* pa) {
			value = val;
			parent = pa;
		}
	};

	//Variables
	const bool red = true;
	const bool black = false;
	node* root;
	int node_count;

	//Functions
	void insertion_relabel(node* n) {
		node* pa = n->parent;
		if (pa == nullptr) {
			n->color = black;
			root = n;
			return;
		}
		node* grand_parent = pa->parent;
		if (grand_parent == nullptr)
			return;
		bool node_is_left_child = pa->left == n;
		bool parent_is_left_child = pa == grand_parent->left;
		node* uncle = parent_is_left_child ? grand_parent->right : grand_parent->left;
		bool uncle_is_red_node = uncle == nullptr ? black : uncle->color;
		if (uncle_is_red_node) {
			pa->color = black;
			grand_parent->color = red;
			uncle->color = black;
		}
		else
			if (parent_is_left_child)
				if (node_is_left_child)
					grand_parent = left_left_case(grand_parent);
				else
					grand_parent = left_right_case(grand_parent);
			else
				if (node_is_left_child)
					grand_parent = right_left_case(grand_parent);
				else
					grand_parent = right_right_case(grand_parent);
		insertion_relabel(grand_parent);
	}

	node swap_colors(node* a, node* b) {
		bool tmp_color = a->color;
		a->color = b->color;
		b->color = tmp_color;
	}

	node* left_left_case(node* n) {
		n->left = right_rotation(n->left);
		swap_colors(n, n->right);
		return n;
	}
	node* left_right_case(node* n) {
		n->left = left_rotation(n->left);
		return left_left_case(n);
	}
	node* right_right_case(node* n) {
		n = left_rotation(n->left);
		swap_colors(n, n->left);
		return n;
	}
	node* right_left_case(node* n) {
		n->right = right_rotation(n->right);
		return right_right_case(n);
	}

	node* right_rotation(node* parent) {
		node* grandparent = parent->parent;
		node* child = parent->left;
		parent->left = child->right;
		if (child->right != nullptr)
			child->right->parent = parent;
		child->right = parent;
		parent->parent = child;
		child->parent = grandparent;
		update_parent_child_link(grandparent, parent, child);
		return child;
	}
	node* left_rotation(node* parent) {
		node* grandparent = parent->parent;
		node* child = parent->right;
		parent->right = child->left;
		if (child->left != nullptr)
			child->left->parent = parent;
		child->left = parent;
		parent->parent = child;
		child->parent = grandparent;
		update_parent_child_link(grandparent, parent, child);
		return child;
	}

	void update_parent_child_link(node* parent, node* old_child, node* new_child) {
		if (parent != nullptr)
			if (parent->left == old_child)
				parent->left = new_child;
			else
				parent->right = new_child;
	}

	node find_min(node n) {
		while (n.left != nullptr)
			n = n.left;
		return n;
	}

	node find_max(node n) {
		while (n.right != nullptr)
			n = n.right;
		return n;
	}
public:
	redBlackTree() {
		root = nullptr;
		node_count = 0;
	}

	int size() {
		return node_count;
	}

	bool empty() {
		return node_count == 0;
	}

	bool contains(T val) {
		node* n = root;
		if (n == nullptr || val == NULL)
			return false;
		while (node != nullptr) {
			int cmp = val - n->vlaue;
			if (cmp < 0)
				n = n->left;
			else if (cmp > 0)
				n = n->right;
			else return true;
		}
		return false;
	}

	bool insert(T val) {
		if (val == NULL)
			return false;
		if (root == nullptr) {
			root = new node(val, nullptr);
			insertion_relabel(root);
			node_count++;
			return true;
		}
		for (node* n = root; ; ) {
			int cmp = val - n->value;
			if (cmp < 0) {
				if (n->left == nullptr) {
					n->left = new node(val, n);
					insertion_relabel(n->left);
					node_count++;
					return true;
				}
				n = n->left;
			}
			else if (cmp > 0) {
				if (n->right == nullptr) {
					n->right = new node(val, n);
					insertoon_relabel(n->left);
					node_count++;
					return true;
				}
				n = n->right;
			}
			else return false;
		}
	}
};