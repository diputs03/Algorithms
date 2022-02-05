#include "graph.h"


void dfs(int at, std::vector<int>* k) {
	vis[at] = vis_token;
	for (int i = 0; i < graph[at].size(); i++)
		if (vis[graph[at][i].to] != vis_token)
			dfs(graph[at][i].to, k);
	k->push_back(at);
}

int* topological_sort() {
	vis_token++;
	int index = n - 1;
	int* order = new int[n];
	for (int at = 0; at < n; at++) {
		if (vis[at] != vis_token) {
			std::vector<int> visited_nodes;
			dfs(at, &(visited_nodes));
			for (int id = 0; id < visited_nodes.size(); id++)
				order[index--] = visited_nodes[id];
		}
	}
	return order;
}