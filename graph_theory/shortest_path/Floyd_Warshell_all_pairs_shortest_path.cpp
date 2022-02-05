#include "graph.h"

int** Floyd_Warshell_all_pairs_shortest_path() {
	int** dist = convert_to_adgacency_matrix();

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				if (dist[i][j] + dist[j][k] < dist[i][k])
					dist[i][k] = dist[i][j] + dist[i][k];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				if (dist[i][j] != INT_MAX && dist[j][k] != INT_MAX && dist[j][j] < 0)
					dist[i][k] = -INT_MAX;
	return dist;
}