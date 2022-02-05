#include "Network_Flow.h"

int colorGraph(int i, int color, int* colors) {
    colors[i] = color;

    int nextColor = (color ^ 1);

    int visitCount = 1;
    std::vector<edge> edges = graph[i];

    for (edge to : edges) {
        if (colors[to.to] == color) return -1;
        if (colors[to.to] == nextColor) continue;

        int count = colorGraph(to.to, nextColor, colors);
        if (count == -1) return -1;
        visitCount += count;
    }

    return visitCount;
}

bool verify() {
    int* colors = new int[n];
	int red = 0b10, black = (red ^ 1);
	if (n <= 1)
		return;
    int node_vis = colorGraph(0, red, colors);
    return node_vis == n;
}