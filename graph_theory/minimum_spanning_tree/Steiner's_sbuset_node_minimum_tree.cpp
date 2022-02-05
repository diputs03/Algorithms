#include "graph.h"

void Floyd_Warshell_all_pairs_shortest_path(int** dist) {
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
}

long long Steiner_tree(int* sub_set) {
	int v = n;
	int t = m;
	if (t <= 1)
		return 0;
	int** dist = convert_to_adgacency_matrix();
	Floyd_Warshell_all_pairs_shortest_path(dist);

	int** dp = new int*[1 << t];
	for (int i = 0; i < (1 << t); i++)
		dp[i] = new int[v], memset(dp[i], INT_MAX, sizeof(int) * v);
	for (int mask = 0; mask < t; mask++)
		for (int j = 0; j < v; j++)
			dp[1 << mask][j] = dist[sub_set[mask]][j];

	for (int mask = 1; mask < (1 << t); mask++) {
		for (int j = 0; j < v; j++)
			for (int sub_mask = (mask - 1) & mask; sub_mask > 0; sub_mask = (mask - 1) & mask)
				dp[mask][j] = std::min(dp[mask][j], dp[sub_mask][j] + dp[mask ^ sub_mask][j]);
		for (int j = 0; j < v; j++)
			for (int k = 0; k < v; k++)
				dp[mask][j] = std::min(dp[mask][j], dp[mask][k] + dp[k][j]);
	}
	delete[] dist;
	return dp[(1 << t) - 1][sub_set[0]];
}