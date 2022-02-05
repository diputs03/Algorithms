#include "graph.h"
#include "union_find.h"

line* convert_to_edge_list() {
	line* edge_list = new line[m];
	int k = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < graph[i].size(); i++)
			edge_list[k++] = graph[i][j];
	return edge_list;
}

bool cmp(line& a, line& b) {
	return a.cost < b.cost;
}

std::pair<int, int*> Kuruskal_minimum_spanning_tree() {
	long long sum = 0L;
	line* edge_list = convert_to_edge_list();
	std::sort(edge_list, edge_list + m, cmp);
	unionFind uf(n);
	for (int i = 0; i < m; i++) {
		if (uf.connected(edge_list[i].from, edge_list[i].to))
			continue;
		uf.unify(edge_list[i].from, edge_list[i].to);
		sum += edge_list[i].cost;
		if (uf.size(0) == n)
			break;
	}
	delete[] edge_list;
	return std::pair<int, int*>(sum, uf.list(0));
}