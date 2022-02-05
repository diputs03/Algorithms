#include "graph.h"

//to every node
int* dijkstra_minimum_cost(int start) {
	int* dist = new int[n];
	memset(dist, INT_MAX, sizeof(int) * n);
	dist[0] = 0;
	std::priority_queue<std::pair<int, int>> pq;
	pq.push(std::pair<int, int>(start, 0));
	while (pq.size() != 0) {
		int index = pq.top().first, min_val = pq.top().second;
		vis[index] = vis_token;
		if (dist[index] < min_val)
			continue;
		for (int i = 0; i < graph[index].size(); i++) {
			if (vis[graph[index][i].to] == vis_token)
				continue;
			int new_dist = dist[index] + graph[index][i].cost;
			if (new_dist < dist[graph[index][i].to]) {
				dist[graph[index][i].to] = new_dist;
				pq.push(std::pair<int, int>(graph[index][i].to, new_dist));
			}
		}
	}
	return dist;
}

//just to the end
int dijkstra_minimum_cost(int start, int end) {
	int* dist = new int[n];
	vis_token++;
	memset(dist, INT_MAX, sizeof(int) * n);
	dist[0] = 0;
	std::priority_queue<std::pair<int, int>> pq;
	pq.push(std::pair<int, int>(start, 0));
	while (pq.size() != 0) {
		int index = pq.top().first, min_val = pq.top().second;
		vis[index] = vis_token;
		if (dist[index] < min_val)
			continue;
		for (int i = 0; i < graph[index].size(); i++) {
			if (vis[graph[index][i].to] == vis_token)
				continue;
			int new_dist = dist[index] + graph[index][i].cost;
			if (new_dist < dist[graph[index][i].to]) {
				dist[graph[index][i].to] = new_dist;
				pq.push(std::pair<int, int>(graph[index][i].to, new_dist));
			}
		}
		if (index = end) {
			int tmp = dist[end];
			delete[] dist;
		}
	}
	delete[] dist;
	return INT_MAX;
}

std::pair<int*, int*>* dijkstra_shortest_path(int start) {
	vis_token++;
	int* dist = new int[n];
	int* prev = new int[n];
	memset(prev, -1, sizeof(int) * n);
	memset(dist, INT_MAX, sizeof(int) * n);
	dist[0] = 0;
	std::priority_queue<std::pair<int, int>> pq;
	pq.push(std::pair<int, int>(start, 0));
	while (pq.size() != 0) {
		int index = pq.top().first, min_val = pq.top().second;
		vis[index] = true;
		if (dist[index] < min_val)
			continue;
		for (int i = 0; i < graph[index].size(); i++) {
			if (vis[graph[index][i].to])
				continue;
			int new_dist = dist[index] + graph[index][i].cost;
			if (new_dist < dist[graph[index][i].to]) {
				prev[graph[index][i].to] = index;
				dist[graph[index][i].to] = new_dist;
				pq.push(std::pair<int, int>(graph[index][i].to, new_dist));
			}
		}
	}
	return new std::pair<int*, int*>(dist, prev);
}

//to every node
std::vector<int>** shortest_path(int start) {
	int* dist = dijkstra_shortest_path(start)->first;
	int* prev = dijkstra_shortest_path(start)->second;
	std::vector<int>** path = new std::vector<int>*[n];
	for (int i = 0; i < n; i++) {
		path[i] = new std::vector<int>;
		if (dist[i] == INT_MAX)
			continue;
		for (int at = i; at != -1; at = prev[at])
			path[i]->push_back(at);
		path[i]->reserve(path[i]->size());
	}
	delete[] dist;
	delete[] prev;
	return path;
}

//just to the end
std::vector<int>* shortest_path(int start, int end) {
	int* dist = dijkstra_shortest_path(start)->first;
	int* prev = dijkstra_shortest_path(start)->second;
	std::vector<int>* path = new std::vector<int>[n];
	for (int at = end; at != -1; at = prev[at])
		path->push_back(at);
	path->reserve(path->size());
	delete[] dist;
	delete[] prev;
	return path;
}