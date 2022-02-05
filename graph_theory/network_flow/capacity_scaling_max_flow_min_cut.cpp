#include "Network_Flow.h"

long long dfs(int node, long long flow, int end, long long delta) {
	if (node == end)
		return flow;
	vis[node] = vis_token;

	for (int i = 0; i < graph[node].size(); i++) {
		long long cap = graph[node][i].remaining_capacity();
		if (cap >= delta && vis[graph[node][i].to] != vis_token) {
			long bottle_neck = dfs(graph[node][i].to, std::min(flow, cap), end, delta);
			if (bottle_neck > 0) {
				graph[node][i].augment(bottle_neck);
				return bottle_neck;
			}
		}
	}
	return 0L;
}

void capacity_scaling(int start, int end) {
	long long delta = (long long)std::pow(2, (int)floor(std::log(delta) / std::log(2)));
	for (long long f = 0; delta > 0; delta /= 2) {
		do {
			vis_token++;
			f = dfs(start, INF, end, delta);
			max_flow += f;
		} while (f != 0);
	}
	
	for (int i = 0; i < n; i++)
		if (vis[i] == vis_token)
			min_cuts[i] = true;
}