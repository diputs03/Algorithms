#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
#include <stack>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include "sparse_table.h"
class line {
public:
	int to;
	int from;
	line() {
		from = to = NULL;
	}
	line(int be, int to) {
		from = be;
		this->to = to;
	}
};
class node {
public:
	int id;
	node* parent;
	std::vector<node*> children;
	node() {
		id = -1;
		parent = nullptr;
	}
	node(int id) {
		this->id = id;
		parent = nullptr;
	}
	node(int id, node* parent) {
		this->id = id;
		this->parent = parent;
	}

	void add_child(node* child) {
		children.push_back(child);
	}

	friend bool equals(node obj1, node obj2) {
		return obj1.id == obj2.id;
	}

	int height() {
		int height_childrens = 0;
		for (int i = 0; i < children.size(); i++)
			height_childrens = std::max(children[i]->height(), height_childrens);
		return height_childrens + 1;
	}
};
class Tree {
public:
	int* vis;
	static int vis_token;
	int n;
	Tree() {
		vis_token = 1;
	}
	std::vector<line>* graph;
	std::vector<int>* tree_center() {
		int* degree = new int[n];
		memset(degree, 0, sizeof(int) * n);
		std::vector<int>* leaves = new std::vector<int>;
		for (int i = 0; i < n; i++) {
			degree[i] = graph[i].size();
			if (degree[i] == 0 || degree[i] == 1) {
				leaves->push_back(i);
				degree[i] = 0;
			}
		}
		int count = leaves->size();
		while (count < n) {
			std::vector<int>* new_leaves = new std::vector<int>;
			for (int n : *leaves) {
				for (line neighbors : graph[n]) {
					degree[neighbors.to]--;
					if (degree[neighbors.to] == 1)
						new_leaves->push_back(neighbors.to);
				}
				degree[n] = 0;
			}
			count += new_leaves->size();
			delete[] leaves;
			leaves = new_leaves;
		}
		delete[] degree;
		return leaves;
	}

private:
	void build_tree(node* n, node* parent) {
		for (int i = 0; i < graph[n->id].size(); i++) {
			node* child = new node(graph[n->id][i].to);
			n->add_child(child);
			build_tree(child, n);
		}
	}
public:
	node* root_tree() {
		node* n = new node(0);
		build_tree(n, nullptr);
		return n;
	}
private:
	int* dfs(int at, int parent) {
		if (vis[at] == vis_token)
			return new int[] {0, parent};
		vis[at] = vis_token;
		int best_dist = 0;
		int index = -1;
		std::vector<line> edges = graph[at];

		for (line to : edges) {
			int* tuple = dfs(to.to, at);
			int dist = tuple[0] + 1;
			if (dist > best_dist) {
				best_dist = dist;
				index = tuple[1];
				delete[] tuple;
			}
		}
		return new int[] {best_dist, index};
	}
public:
	int tree_diameter(int start) {
		vis_token++;
		int furthest_index = dfs(start, -1)[1];

		if (furthest_index == -1)
			return 0;

		vis_token++;

		int diameter = dfs(furthest_index, -1)[0] - 1;

		return diameter;
	}
private:
	node* nodeOrder;
	int* nodeDepth;
	int* last;
	int tourIndex;
	void dfs(node* n, long depth) {
		if (n == nullptr)
			return;
		visit(n, depth);
		for (node* child : n->children) {
			dfs(child, depth + 1);
			visit(n, depth);
		}
	}
	void visit(node* n, long depth) {
		nodeOrder[tourIndex] = *n;
		nodeDepth[tourIndex] = depth;
		last[n->id] = tourIndex;
		tourIndex++;
	}
public:
	node lca(int idx1, int idx2) {
		int eulerTourSize = 2 * n - 1;
		node* nodeOrder = new node[eulerTourSize];
		long long* nodeDepth = new long long [eulerTourSize];
		int* last = new int[n];
		tourIndex = 0;
		dfs(root_tree(), 0);
		MinSparseTable* sparseTable = new MinSparseTable(nodeDepth, eulerTourSize);
		int l = std::min(last[idx1], last[idx2]);
		int r = std::max(last[idx1], last[idx2]);
		int i = sparseTable->queryIndex(l, r);
		return nodeOrder[i];
	}
};
std::string encode(node* n) {
	if (n == nullptr) {
		return "";
	}
	std::vector<std::string>* labels = new std::vector<std::string>;
	for (node* child : n->children) {
		labels->push_back(encode(child));
	}
	std::sort(labels->begin(), labels->end());
	std::string sb;
	for (std::string label : *labels) {
		sb.append(label);
	}
	delete[] labels;
	return "(" + sb + ")";
}
bool tree_isomorphic(Tree* tree1, Tree* tree2) {
	std::vector<int>* centers1 = tree1->tree_center();
	std::vector<int>* centers2 = tree2->tree_center();
	node* rooted_Tree1 = tree1->root_tree();
	std::string tree1_code = encode(rooted_Tree1);

	for (int center : *centers2) {
		node* rooted2 = tree2->root_tree();
		std::string tree2_code = encode(rooted2);
		if (tree1_code == tree2_code)
			return true;
	}
	return false;
}