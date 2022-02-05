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

const int MAX_node = 100;
const int MAX_line = 1000;

class line {
public:
	int to;
	int cost;
	int from;
	line() {
		from = to = NULL;
		cost = INT_MAX;
	}
	line(int be, int to, int cost) {
		from = be;
		this->to = to;
		this->cost = cost;
	}
};

std::vector<line> graph[MAX_node];

//# of nodes
int n;

//# of edges
int m;

void add_directed_edge(int from, int to, int cost) {
	graph[from].push_back(line(from, to, cost));
}

void add_undirected_edge(int from, int to, int cost) {
	add_directed_edge(from, to, cost);
	add_directed_edge(to, from, cost);
}

int** convert_to_adgacency_matrix(){
	int** mat = new int*[n];
	for (int i = 0; i < n; i++)
		mat[i] = new int[n], memset(mat[i], INT_MAX, sizeof(int) * n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < graph[i].size(); j++)
			mat[i][graph[i][j].to] = graph[i][j].cost;
	return mat;
}

int vis_token = 1;

int* vis = new int[n];