#include "graph.h"

int tsp(int i, int state, int** memo, int** prev, int** dist, int start) {
	if (state == (1 << n) - 1)
		return dist[i][start];
	if (memo[i][state] != INT_MAX)
		return memo[i][state];

	int min_cost = INT_MAX;
	int index = -1;
	for (int next = 0; next < n; next++) {
		if ((state & (1 << next)) != 0)
			continue;
		int next_state = state | (1 << next);
		int new_cost = dist[i][next] + tsp(next, next_state, memo, prev, dist, start);
		if (new_cost < min_cost) {
			min_cost = new_cost;
			index = next;
		}
	}
	prev[i][state] = index;
	return memo[i][state] = min_cost;
}

std::pair<int, std::list<int>*> travelling_salesman_problem(int start) {
	int** dist = convert_to_adgacency_matrix();
	int state = 1 << start;
	std::list<int>* tour = new std::list<int>;
	int** memo = new int* [n];
	for (int i = 0; i < n; i++)
		memo[i] = new int[1 << n], memset(memo[i], INT_MAX, sizeof(int) * (1 << n));
	int** prev = new int* [n];
	for (int i = 0; i < n; i++)
		prev[i] = new int[1 << n];
	int min_tour_cost = tsp(start, state, memo, prev, dist, start);

	int index = start;
	while (true) {
		tour->push_back(index);
		int next_index = prev[index][state];
		if (next_index == INT_MAX)
			break;
		int next_state = state | (1 << next_index);
		state = next_state;
		index = next_index;
	}
	tour->push_back(start);
	delete[] dist;
	delete[] memo;
	delete[] prev;
	return std::pair<int, std::list<int>*>(min_tour_cost, tour);
}