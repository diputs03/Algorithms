#include "graph.h"

void dfs(int at, int parent, std::vector<std::pair<int, int>>* bridge, int id, int* low, int* ids) {
	vis[at] = vis_token;
	low[at] = ids[at] = ++id;

	for (int to = 0; to < graph[at].size(); to++)
		if (graph[at][to].to == parent)
			continue;
		else if (!vis[graph[at][to].to]) {
			dfs(graph[at][to].to, at, bridge, id, low, ids, vis);
			low[at] = std::min(low[at], low[graph[at][to].to]);
			if (ids[at] < low[graph[at][to].to]) {
				bridge->push_back(std::pair<int, int>(at, graph[at][to].to));
			}
		}
		else
			low[at] = std::min(low[at], ids[graph[at][to].to]);
}

std::vector<std::pair<int, int>>* bridges() {
	vis_token++;
	int id = 0;
	int* low = new int[n];
	int* ids = new int[n];
	std::vector<std::pair<int, int>>* bridge = new std::vector<std::pair<int, int>>;

	for (int i = 0; i < n; i++)
		if (vis[i] != vis_token)
			dfs(i, -1, bridge, id, low, ids);

	delete[] low;
	delete[] ids;
	return bridge;
}