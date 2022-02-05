#include "graph.h"


void dfs(int at) {
	vis[at] = vis_token;
	for (int i = 0; i < graph[at].size(); i++)
		if (vis[graph[at][i].to] != vis_token)
			dfs(graph[at][i].to);
}

void depth_first_search(int start) {
	vis_token++;
	dfs(start);
}