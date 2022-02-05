#include "Network_Flow.h"

std::list<edge>* augmenting_path(int start, int end) {
	class node {
	public:
		int id;
		long long value;
		node(int id, long long value) {
			this->id = id;
			this->value = value;
		}
		int compare_to(node o) {
			return (int)(value - o.value);
		}
	};
	long long* dist = new long long[n];
	memset(dist, INF, sizeof(long long) * n);
	dist[start] = 0;
	vis_token++;
	edge* prev = new edge[n];
	std::priority_queue<node> pq;
	pq.push(node(start, 0));
	while (!pq.empty()) {
		node n = pq.top();
		pq.pop();
		vis[n.id] = vis_token;
		if (dist[n.id] < n.value)
			continue;
		std::vector<edge> edges = graph[n.id];
		for (int i = 0; i < edges.size(); i++) {
			edge e = edges[i];
			if (vis[e.to] == vis_token)
				continue;
			long long new_dist = dist[e.from] + e.cost;
			if (e.remaining_capacity() > 0 && new_dist < dist[e.to]) {
				prev[e.to] = e;
				dist[e.to] = new_dist;
				pq.push(node(e.to, dist[e.to]));
			}
		}
	}
	std::list<edge>* path = new std::list<edge>;
	if (dist[end] == INF)
		return path;
	for (int from = 0; from < n; from++)
		for (edge e : graph[from])
			if (e.remaining_capacity() > 0)
				e.cost += dist[from] - dist[e.to];
			else
				e.cost = 0;
	for (edge* e = &prev[end]; e != nullptr; e = &prev[e->from])
		path->push_front(*e);
	delete[] dist;
	delete[] prev;
	return path;
}

void Johnsons_max_flow(int start, int end) {
	long long* dist = new long long[n];
	memset(dist, INF, sizeof(long long) * n);
	dist[start] = 0;
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < graph[j].size(); j++)
				if (graph[j][k].remaining_capacity() > 0 && dist[j] + graph[j][k].cost < dist[graph[j][k].to])
					dist[graph[j][k].to] = dist[j] + graph[j][k].cost;

	for (int from = 0; from < n; from++)
		for (edge e : graph[from])
			if (e.remaining_capacity() > 0)
				e.cost += dist[from] - dist[e.to];
			else
				e.cost = 0;

	std::list<edge>* path;
	while ((delete[] path, path = augmenting_path(start, end))->size() != 0) {

		long long bottleNeck = LONG_MAX;
		for (edge edge : *path)
			bottleNeck = std::min(bottleNeck, edge.remaining_capacity());

		for (edge edge : *path) {
			edge.augment(bottleNeck);
			min_cost += bottleNeck * edge.original_cost;
		}
		max_flow += bottleNeck;

	}
	delete[] path;
	delete[] dist;
}