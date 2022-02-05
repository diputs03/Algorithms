#include "graph.h"

bool in(int i, int sub_set) {
	return ((1 << i) & sub_set) != 0;
}

void combinations(int set, int at, int r, int n, std::list<int>* subsets) {
	int elem_left_picking = n - at;
	if (elem_left_picking < r)
		return;
	if (r == 0)
		subsets->push_back(set);
	else
		for (int i = at; i < n; i++) {
			set ^= (1 << i);
			combinations(set, i + 1, r - 1, n, subsets);

			set ^= (1 << i);
		}
}

std::list<int>* combinations(int r, int n) {
	std::list<int>* subsets = new std::list<int>;
	combinations(0, 0, r, n, subsets);
	return subsets;
}

int find_min_cost(int** mat, int** memo, int start) {
	int END_STATE = (1 << n) - 1;
	int min_tour_cost = INT_MAX;
	for (int e = 0; e < n; e++) {
		if (e == start)
			continue;
		int tour_cost = memo[e][END_STATE] + mat[e][start];
		if (tour_cost < min_tour_cost)
			min_tour_cost = tour_cost;
	}
	return min_tour_cost;
}

int* find_optimal_tour(int** mat, int** memo, int start) {
	int last_index = start;
	int state = (1 << n) - 1;
	int* tour = new int[n + 1];
	for (int i = n - 1; i >= 1; i--) {
		int index = -1;
		for (int j = 0; j < n; j++) {
			if (j == start || !in(j, state))
				continue;
			if (index == -1)
				index = j;
			int prev_dist = memo[index][state] + mat[index][last_index];
			int new_dist = memo[j][state] + mat[j][last_index];
			if (new_dist < prev_dist)
				index = j;
		}
		tour[i] = index;
		state = state ^ (1 << index);
		last_index = index;
	}
	tour[0] = start;
	tour[n] = start;
	delete[] mat;
	delete[] memo;
	return tour;
}

std::pair<int, int*> travelling_salesman_problem(int start) {
	int** mat = convert_to_adgacency_matrix();
	int** memo = new int*[n];
	for (int i = 0; i < n; i++)
		memo[i] = new int[std::pow(2, n)], memset(memo[i], INT_MAX, sizeof(int) * std::pow(2, n));

	for (int i = 0; i < n; i++)
		if (i == start)
			continue;
		else
			memo[i][1 << start | 1 << i] = mat[start][i];

	for (int r = 3; r <= n; r++) {
		for (int sub_set : *(combinations(r, n))) {
			if (!in(start, sub_set)) {
				for (int next = 0; next < n; next++) {
					if (next == start || !in(next, sub_set))
						continue;
					int state = sub_set ^ (1 << next);
					int min_dist = INT_MAX;
					for (int e = 0; e < n; e++) {
						if (e == start || e == next || !in(e, sub_set))
							continue;
						int new_dist = memo[e][state] + mat[e][next];
						if (new_dist < min_dist)
							min_dist = new_dist;
					}
					memo[next][sub_set] = min_dist;
				}
			}
		}
	}

	return std::pair<int, int*>(find_min_cost(mat, memo, start), find_optimal_tour(mat, memo, start));
}