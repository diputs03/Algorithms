#include "graph.h"
#include "union_find.h"

int connected_components() {
	unionFind uf(n);
	for (int i = 0; i < n; i++) {
		std::vector<line> edges = graph[i];
		for (line edge : edges)
			uf.unify(edge.from, edge.to);
	}
	return uf.components();
}