#include "data_structure.h"

class trie {
private:
	//Classes
	class node {
	public:
		char ch;
		int count;
		bool word_ending;
		std::map<char, node*>* children;
		node() {
			count = 0;
			word_ending = false;
			children = new std::map<char, node*>;
		}

		node(char ch) {
			this->ch = ch;
		}

		void add_child(node* n, char c) {
			children->insert(std::pair<char, node*>(c, n));
		}
	};
	//Variables
	static const char root_character = '\0';
	node* root;

	//Functions
	void clear(node* n) {
		if (n == nullptr)
			return;
		delete n->children;
		n->children = nullptr;
	}

public:
	trie() {
		root = new node(root_character);
	}

	bool insert(std::string* key, int num_inserts) {
		if (key == nullptr || num_inserts <= 0)
			return false;
		node* n = root;
		bool created_new_node = false;
		bool prefix = false;
		for (int i = 0; i < (int)key->length(); i++) {
			char ch = key->at(i);
			node* next_node = n->children->find(ch)->second;
			if (next_node == nullptr) {
				next_node = new node(ch);
				n->add_child(next_node, ch);
				created_new_node = true;
			}
			else if (next_node->word_ending)
				prefix = true;
			
			n = next_node;
			n->count += num_inserts;
		}

		if (n != root)
			n->word_ending = true;
		return prefix || !created_new_node;
	}

	bool insert(std::string* key) {
		return insert(key, 1);
	}

	bool remove(std::string* key, int num_removes) {
		if (!contains(key) || num_removes <= 0)
			return false;
		node* n = root;
		for (int i = 0; i < (int)key->length(); i++) {
			char ch = key->at(i);
			node* curr_node = n->children->find(ch)->second;
			curr_node->count -= num_removes;

			if (curr_node->count <= 0) {
				n->children->erase(ch);
				curr_node->children = nullptr;
				curr_node = nullptr;
				delete curr_node;
				return true;
			}

			n = curr_node;
		}
		return true;
	}

	bool remove(std::string* key) {
		return remove(key, 1);
	}

	bool contains(std::string* key) {
		return count(key) != 0;
	}

	int count(std::string* key) {
		if (key == nullptr)
			return 0;
		node* n = root;
		for (int i = 0; i < key->length(); i++) {
			char ch = key->at(i);
			if (n == nullptr)
				return 0;
			n = n->children->find(ch)->second;
		}
		if (n != nullptr)
			return n->count;
		return 0;
	}

	void clear() {
		root->children = nullptr;
		root = new node(root_character);
	}
};