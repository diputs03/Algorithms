#include "graph.h"

void dfs(int at, int* components, int* components_count) {
	vis[at] = vis_token;
	components[at] = *components_count;
	for (line to : graph[at])
		if (vis[to.to] != vis_token)
			dfs(to.to, components, components_count);
}

int connected_components() {
	int* components = new int[n];
	int components_count = 0;
	vis_token++;
	for(int i = 0; i < n; i++)
		if (vis[i] != vis_token) {
			components_count++;
			dfs(i, components, &components_count);
		}
	delete[] components;
	return components_count;
}