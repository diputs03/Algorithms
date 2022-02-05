#include "Network_Flow.h"

std::list<edge>* get_augmenting_path(int start, int end, long long* dist) {
	edge** prev = new edge*[n];

	for (int i = 0; i < n - 1; i++)
		for (int from = 0; from < n; from++)
			for (edge edge : graph[from])
				if (edge.remaining_capacity() > 0 && dist[from] + edge.cost < dist[edge.to]) {
					dist[edge.to] = dist[from] + edge.cost;
					prev[edge.to] = &edge;
				}

	std::list<edge>* path = new std::list<edge>;
	for (edge* edge = prev[end]; edge != nullptr; edge = prev[edge->from])
		path->push_back(*edge);
	return path;
}

std::list<edge>* Bellman_Ford_max_flow(int start, int end) {
	long long* dist = new long long[n];
	memset(dist, INF, sizeof(long long) * n);
	dist[start] = 0;
	std::list<edge>* path;
	while ((delete[] path, path = get_augmenting_path(start, end, dist))->size() != 0) {

		long long bottleNeck = LONG_MAX;
		for (edge edge : *path)
			bottleNeck = std::min(bottleNeck, edge.remaining_capacity());

		for (edge edge : *path) {
			edge.augment(bottleNeck);
			min_cost += bottleNeck * edge.original_cost;
		}
		max_flow += bottleNeck;

	}
	delete[] dist;
	delete[] path;
	return path;
}