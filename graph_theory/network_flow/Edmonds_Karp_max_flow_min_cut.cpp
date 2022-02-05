#include "Network_Flow.h"

long long bfs(int start, int end) {
	edge** prev = new edge*[n];
	std::queue<int> q;
	vis[start] = vis_token;
	q.push(start);
	while (!q.empty()) {
		int node = q.front();
		q.pop();
		if (node == end)
			break;

		for (int i = 0; i < graph[node].size(); i++) {
			long long cap = graph[node][i].remaining_capacity();
			if (cap > 0 && vis[graph[node][i].to] != vis_token) {
				vis[graph[node][i].to] = vis_token;
				prev[graph[node][i].to] = &graph[node][i];
				q.push(graph[node][i].to);
			}
		}
	}

	if (prev[end] == NULL)
		return 0;

	long long bottle_neck = LONG_MAX;

	for (edge* e = prev[end]; e != nullptr; e = prev[e->from])
		bottle_neck = std::min(bottle_neck, e->remaining_capacity());

	for (edge* e = prev[end]; e != nullptr; e = prev[e->from])
		e->augment(bottle_neck);
	delete[] prev;
	return bottle_neck;
}

void Edmonds_Karp_max_flow(int start, int end) {
	memset(min_cuts, false, sizeof(bool) * n);
	long long flow;
	do {
		vis_token++;
		flow = bfs(start, end);
		max_flow += flow;
	} while (flow != 0);

	for (int i = 0; i < n; i++)
		if (vis[i] == vis_token)
			min_cuts[i] = true;
}