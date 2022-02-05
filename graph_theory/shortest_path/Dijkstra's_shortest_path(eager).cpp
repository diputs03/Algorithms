#include "graph.h"

bool contains(std::priority_queue<std::pair<line, int>, std::less<std::pair<line, int>>>* ipq, int node) {
	std::stack<std::pair<line, int>> tmp;
	bool check = false;
	for (int i = 0; i < ipq->size(); i++) {
		if (ipq->top()->second == node) {
			check = true;
			break;
		}
		tmp.push(ipq->top());
	}
	while (!tmp.empty()) {
		ipq->push(tmp.top());
		tmp.pop();
	}
	return check;
}

void decrease_key(std::priority_queue<std::pair<line, int>, std::less<std::pair<line, int>>>* ipq, int node, line l) {
	std::stack<std::pair<line, int>> tmp;
	for (int i = 0; i < ipq->size(); i++) {
		if (ipq->top()->first == l)
			break;
		tmp.push(ipq->top());
	}
	std::pair<line, int> k = ipq->top();
	ipq->pop();
	k.second = node;
	ipq->push(k);
	while (!tmp.empty()) {
		ipq->push(tmp.top());
		tmp.pop();
	}
}

int* dijkstra(int start) {
	vis_token++;
	int* dist = new int[n];
	memset(dist, INT_MAX, sizeof(int) * n);
	dist[0] = 0;
	std::priority_queue<std::pair<line, int>, std::less<std::pair<line, int>>> ipq;
	ipq.push(std::pair<int, int>(start, 0));
	while (ipq.size() != 0) {
		int index = ipq.top().first, min_val = ipq.top().second;
		vis[index] = vis_token;
		if (dist[index] < min_val)
			continue;
		for (int i = 0; i < graph[index].size(); i++) {
			if (vis[graph[index][i].to] == vis_token)
				continue;
			int new_dist = dist[index] + graph[index][i].cost;
			if (!contains(&ipq, graph[index][i].to))
				ipq.push(std::pair<int, int>(graph[index][i].to, new_dist));
			else
				decrease_key(&ipq, new_dist, graph[index][i]);
		}
	}
	return dist;
}