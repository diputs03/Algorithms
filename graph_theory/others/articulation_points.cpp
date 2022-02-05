#include "graph.h"

void dfs(int root, int at, int parent, int* out, int* low, int* ids, int* id, bool* a_point) {
	if (parent == root)
		*out++;
	vis[at] = vis_token;
	low[at] = ids[at] = *id++;
	std::vector<line> edges = graph[at];
	for (line to : edges) {
		if (to.to == parent)
			continue;
		if (vis[to.to] != vis_token) {
			dfs(root, to.to, at, out, low, ids, id, a_point);
			low[at] = std::min(low[at], low[to.to]);
			if (ids[at] < low[to.to])
				a_point[at] = true;
			else
				low[at] = std::min(low[at], ids[to.to]);
		}
	}
}

bool* articulation_points() {
	int id = 0;
	int* low = new int[n];
	int* ids = new int[n];
	bool* a_point = new bool[n];
	memset(a_point, false, sizeof(bool) * n);
	vis_token++;
	int out;
	for(int i = 0; i < n; i++)
		if (vis[i] != vis_token) {
			out = 0;
			dfs(i, i, -1, &out, low, ids, &id, a_point);
			a_point[i] = (out > 1);
		}
	delete[] low;
	delete[] ids;
	return a_point;
}