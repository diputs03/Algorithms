#include "Network_Flow.h"

bool bfs(int start, int* level, int end) {
	memset(level, -1, sizeof(int) * n);
	level[start] = 0;
	std::deque<int> q;
	q.push_back(start);
	while (!q.empty()) {
		int node = q.front();
		q.pop_front();
		for (int i = 0; i < graph[node].size(); i++) {
			long long cap = graph[node][i].remaining_capacity();
			if (cap > 0 && level[graph[node][i].to] == -1) {
				level[graph[node][i].to] = level[node] + 1;
				q.push_back(graph[node][i].to);
			}
		}
	}
	return level[end] != -1;
}

long long dfs(int at, int* next, long long flow, int end, int* level) {
	if (at == end)
		return flow;
	int num_edge = graph[at].size();
	for (; next[at] < num_edge; next[at]++) {
		edge e = graph[at][next[at]];
		long long cap = e.remaining_capacity();
		if (cap > 0 && level[e.to] == level[at] + 1) {
			long long bottle_neck = dfs(e.to, next, std::min(flow, cap), end, level);
			if (bottle_neck > 0) {
				e.augment(bottle_neck);
				return bottle_neck;
			}
		}
	}
	return 0;
}

void Dinic_max_flow(int start, int end) {
	int* level = new int[n];
	int* next = new int[n];

	while (bfs(start, level, end)) {
		memset(next, 0, sizeof(int) * n);
		for (long long f = dfs(start, next, INF, end, level); f != 0; f = dfs(start, next, INF, end, level))
			max_flow += f;
	}

	for (int i = 0; i < n; i++)
		if (level[i] != -1)
			min_cuts[i] = true;
}