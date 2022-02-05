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

class edge {
public:
	int to;
	long long cost;
	int from;
	long long flow;
	edge* residual;
	long long capacity, original_cost;
	edge() {
		from = -1;
		to = -1;
		cost = 0;
		flow = 0;
		residual = nullptr;
		capacity = 0;
		original_cost = 0;
	}
	edge(int from, int end, long long capacity) {
		this->from = from;
		this->to = end;
		cost = 0;
		flow = 0;
		residual = nullptr;
		this->capacity = capacity;
		original_cost = 0;
	}
	edge(int from, int end, long long cost, long long capacity) {
		this->from = from;
		this->to = end;
		this->cost = cost;
		flow = 0;
		residual = nullptr;
		this->capacity = capacity;
		original_cost = 0;
	}

	bool is_residual() {
		return capacity == 0;
	}

	long long remaining_capacity() {
		return capacity - flow;
	}

	void augment(long bottleNeck) {
		flow += bottleNeck;
		residual->flow -= bottleNeck;
	}
};

std::vector<edge> graph[MAX_node];

//# of nodes
int n;

//# of edges
int m;

long long max_flow = 0;

long long min_cost = 0;

bool* min_cuts = new bool[n];

void add_directed_edge(int from, int to, int cap) {
	edge e1(from, to, cap);
	edge e2(to, from, 0);
	e1.residual = &e2;
	e2.residual = &e1;
	graph[from].push_back(e1);
	graph[to].push_back(e2);
}

void add_undirected_edge(int from, int to, int cap) {
	add_directed_edge(from, to, cap);
	add_directed_edge(to, from, cap);
}

const long long INF = LONG_MAX / 2;

int vis_token = 1;

int* vis = new int[n];