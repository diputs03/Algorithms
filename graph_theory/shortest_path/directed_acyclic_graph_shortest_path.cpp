#include "graph.h"

int* topological_sort();

int* dag_shortest_path(int start) {
	int* top_sort = topological_sort();
	int* dist = new int[n];
	memset(dist, -1, sizeof(int) * n);
	dist[start] = 0;

	for (int i = 0; i < n; i++) {
		int node_index = top_sort[i];
		if (dist[node_index] != -1)
			for (int i = 0; i < graph[node_index].size(); i++) {
				int new_dist = dist[node_index] + graph[node_index][i].cost;
				if (dist[graph[node_index][i].to] == -1)
					dist[graph[node_index][i].to] = new_dist;
				else
					dist[graph[node_index][i].to] = std::min(dist[graph[node_index][i].to], new_dist);
			}
	}
	delete[] top_sort;
	return dist;
}