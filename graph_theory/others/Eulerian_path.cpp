#include "graph.h"

void count_in_out_degrees(int* in, int* out) {
	for(int i = 0; i < n; i++)
		for (int j = 0; j < graph[i].size(); i++) {
			out[i]++;
			in[graph[i][j].to]++;
		}
}

bool has_Eulerian_path(int* in, int* out) {
	int start = 0, end = 0;
	for (int i = 0; i < n; i++)
		if (out[i] - in[i] > 1 || in[i] - out[i] > 1)
			return false;
		else if (out[i] - in[i] == 1)
			start++;
		else if (in[i] - out[i] == 1)
			end++;
	return (!end && start) || (end && start);
}

int find_start_node(int* in, int* out) {
	int start = 0;
	for (int i = 0; i < n; i++) {
		if (out[i] - in[i] == 1)
			return i;
		if (out[i] > 0)
			start = i;
	}
	return start;
}

void dfs(int at, std::list<int>* path, int* in, int* out) {
	while (out[at] != 0) {
		int next_edge = graph[at][--out[at]].to;
		dfs(next_edge, path, in, out);
	}
	path->push_front(at);
}

std::list<int>* Eulerian_path() {
	int* in = new int[n];
	int* out = new int[n];
	std::list<int>* path = new std::list<int>;
	count_in_out_degrees(in, out);
	if (!has_Eulerian_path(in, out))
		return nullptr;
	dfs(find_start_node(in, out), path, in, out);
	if (path->size() == m + 1) {
		delete[] in;
		delete[] out;
		return path;
	}
	delete[] in;
	delete[] out;
	return nullptr;
}