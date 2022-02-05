#include "graph.h"

int* Bellman_Ford_shortest_path(int start) {
	int* dist = new int[n];
	memset(dist, INT_MAX, sizeof(int) * n);
	dist[start] = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; i++)
			for (int k = 0; k < graph[j].size(); k++)
				if (dist[j] + graph[j][k].cost < dist[graph[j][k].to])
					dist[graph[j][k].to] = dist[j] + graph[j][k].cost;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < graph[j].size(); k++)
				if (dist[j] + graph[j][k].cost < dist[graph[j][k].to])
					dist[graph[j][k].to] = -INT_MAX;

	return dist;
}