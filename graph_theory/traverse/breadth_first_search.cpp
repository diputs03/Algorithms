#include "graph.h"

void breadth_first_search(int start) {
	vis_token++;
	std::queue<int> q;
	q.push(start);
	while (q.empty()) {
		int node = q.front();
		q.pop();

		for(int i = 0; i < graph[node].size(); i++)
			if (vis[graph[node][i].to] != vis_token) {
				q.push(graph[node][i].to);
				vis[graph[node][i].to] = vis_token;
			}
	}
}