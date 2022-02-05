#include "graph.h"

void dfs1(int from, std::vector<int>* post_order) {
	if (vis[from] == vis_token)
		return;
	vis[from] = vis_token;
	for (line to : graph[from])
		dfs1(to.to, post_order);
	post_order->push_back(from);
}

void dfs2(int from, int* sccs, int sccs_cnt) {
	if (vis[from] == vis_token)
		return;
	vis[from] = vis_token;
	for (line to : graph[from])
		dfs2(to.to, sccs, sccs_cnt);
	sccs[from] = sccs_cnt;
}

std::multimap<int, std::list<int>>* Kosaraju_strongly_connected_components() {
	vis_token++;
	int* sccs = new int[n];
	int sccs_cnt;
	std::vector<int>* post_order = new std::vector<int>;
	std::multimap<int, std::list<int>>* multi_map = new std::multimap<int, std::list<int>>;
	vis_token++;

	for (int i = 0; i < n; i++)
		dfs1(i, post_order);
	vis_token++;
	post_order->reserve(n);
	for (int node : *post_order)
		if (vis[node] != vis_token)
			dfs2(node, sccs, sccs_cnt), sccs_cnt++;
	for (int i = 0; i < n; i++) {
		auto pos_key = multi_map->find(n);
		if (pos_key == multi_map->end())
			multi_map->emplace(sccs[i], new std::list<int>);
		auto pos = multi_map->equal_range(sccs[i]);
		std::multimap<int, std::list<int>>::iterator it;
		for (it = pos.first; it != pos.second; it++)
			if (it->first == sccs[i])
				it->second.push_back(i);
	}
	delete[] sccs;
	delete[] post_order;
	return multi_map;
}