#pragma once
#include "data_structure.h"

class skipList {
private:
	//Classes
	class key {
	public:
		int k;
		key() {

		}
		key(int kk) {
			k = kk;
		}
		int compare_to(key k2) {
			return k - k2.k;
		}
	};
	class node {
	public:
		node* left;
		node* right;
		node* up;
		node* down;
		int height;
		int left_distance;
		key k;

		node(key kk) {
			k = kk;
		}

		int compare_to(node* n2) {
			return k.compare_to(n2->k);
		}

		node* find(node* f) {
			if (f->compare_to(right) >= 0)
				return right->find(f);
			else if (down != nullptr)
				return down->find(f);
			return this;
		}

		void insert(node* n2, node* lower, int insert_height, int distance) {
			if (height <= insert_height) {
				n2->left = this;
				n2->right = right;
				n2->down = lower;
				right->left = n2;
				right = n2;
				if (lower != nullptr)
					lower->up = n2;
				n2->height = height;
				n2->left_distance = distance;
				n2->right->left_distance -= n2->left_distance - 1;
				node* curr = this;
				while (curr->up == nullptr) {
					distance += curr->left_distance;
					curr = curr->left;
				}
				curr = curr->up;
				curr->insert(new node(n2->k), n2, insert_height, distance);
			}
			else {
				node* curr = this;
				curr->right->left_distance++;
				while (curr->left != nullptr || curr->up != nullptr) {
					while (curr->up == nullptr)
						curr = curr->left;
					curr = curr->up;
					curr->right->left_distance++;
				}
			}
		}

		void remove(node* n2) {
			node* curr = this;
			if (curr->compare_to(n2) != 0)
				return;
			while (curr->up != nullptr) {
				curr->left->right = curr->right;
				curr->right->left = curr->left;
				curr->right->left_distance += curr->left_distance - 1;
				curr = curr->up;
			}
			curr->left->right = curr->right;
			curr->right->left = curr->left;
			curr->right->left_distance += curr->left_distance - 1;
			while (curr->left != nullptr || curr->up != nullptr) {
				while (curr->up != nullptr)
					curr = curr->left;
				curr = curr->up;
				curr->right->left_distance--;
			}
		}
	};
	int height;
	node* head;
	node* tail;
public:
	skipList(int height, key min_key, key max_key, int h) {
		srand(time(NULL));
		this->height = height;
		head = new node(min_key);
		tail = new node(max_key);
		node* curr_l = head;
		node* curr_r = tail;
		for (int i = 0; i <= h; i++) {
			curr_l->right = curr_r;
			curr_r->left = curr_l;
			curr_l->down = new node(curr_l->k);
			curr_l->down->up = curr_l;
			curr_r->down = new node(curr_r->k);
			curr_r->down->up = curr_r;
			curr_l->left_distance = 0;
			curr_r->left_distance = 1;
			curr_l->height = height - i;
			curr_r->height = height - i;
			curr_l = curr_l->down;
			curr_r = curr_r->down;
		}
		curr_l->up->down = nullptr;
		curr_r->up->down = nullptr;
	}

	void insert(node* n2) {
		int r = rand();
		if (r < 0)
			r *= -1;
		int node_height = r - (32 - (height - 1));
		head->find(n2)->insert(n2, nullptr, node_height, 1);
	}

	void remove(node* n2) {
		head->find(n2)->remove(n2);
	}

	int get_rank(node* n2) {
		node* curr = head->find(n2);
		if (curr->compare_to(n2) != 0)
			return -1;
		int dist_sum = 0;
		while (curr->left != nullptr) {
			while (curr->up != nullptr)
				curr = curr->up;
			dist_sum += curr->left_distance;
			curr = curr->left;
		}
		return dist_sum;
	}
};