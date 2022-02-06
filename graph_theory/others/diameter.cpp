#include "graph.h"

int eccentricities(int node) {
    std::deque<int> q;
    int depth_token = -1;

    q.push_back(node);
    q.push_back(depth_token);
    vis[node] = vis_token;
    int depth = 0;
    while (true) {
        int id = q.front();
        q.pop_front();
        if (id == depth_token) {
            if (q.empty())
                break;
            q.push_back(depth_token);
            depth++;
        }
        else {
            std::vector<line>* edges = &graph[id];
            if (edges != nullptr)
                for(line edge : *edges)
                    if (vis[edge.to] != vis_token) {
                        vis[edge.to] = vis_token;
                        q.push_back(edge.to);
                    }
        }
    }
    return depth;
}

int diameter() {
	int diameter = 0;
	int radius = INT_MAX;
    for(std::vector<line> edges : graph)
        for (line nodeID : edges) {
            int eccentricity = eccentricities(nodeID.from);
            diameter = std::max(diameter, eccentricity);
            radius = std::min(radius, eccentricity);
        }
    return diameter;
}