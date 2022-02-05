#include "Network_Flow.h"

long long dfs(int node, long long flow, int start, int end) {
	if (node == end)
		return flow;
	vis[node] = vis_token;
	for (int i = 0; i < graph[node].size(); i++) {
		long long rcap = graph[node][i].remaining_capacity();
		if (rcap > 0 && vis[graph[node][i].to] != vis_token) {
			long long bottle_neck = dfs(graph[node][i].to, std::min(flow, rcap), start, end);
			if (bottle_neck > 0) {
				graph[node][i].augment(bottle_neck);
				return bottle_neck;
			}
		}
	}
	return 0;
}

void Ford_Fulkson_max_flow(int start, int end) {
	memset(min_cuts, false, sizeof(bool) * n);
	for (long long f = dfs(start, INF, start, end); f != 0; f = dfs(start, INF, start, end)) {
		vis_token++;
		max_flow += f;
	}

	for (int i = 0; i < n; i++)
		if (vis[i] == vis_token)
			min_cuts[i] = true;
}