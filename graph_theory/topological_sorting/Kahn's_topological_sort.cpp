#include "graph.h"

int* kahn_topological_sort() {
	int* in = new int[n];
	memset(in, 0, sizeof(int) * n);
	for (std::vector<line> edges : graph)
		for (line to : edges)
			in[to.to]++;
	std::queue<int> q;
	for (int i = 0; i < n; i++)
		if (in[i] == 0)
			q.push(i);
	int index = 0;
	int* order = new int[n];
	while (!q.empty()) {
		int at = q.front();
		q.pop();
		order[index++] = at;
		for (line to : graph[at]) {
			in[to.to]--;
			if (in[to.to] == 0)
				q.push(to.to);
		}
	}
	delete[] in;
	return order;
}