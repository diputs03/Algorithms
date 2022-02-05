#include <iostream>
#include <math.h>
#include <algorithm>

int median_of_medians(int arr[]) {
	std::sort(arr, arr + 5);
	return arr[2];
}

//return ith smallest element
int deterministic_selection(int arr[], int size, int i) {
	if (size == 1)
		return arr[0];
	int C[100];
	int k;
	for (k = 0; k < size / 5; k++)
		C[k] = median_of_medians(arr + k * 5);
	if ((k - 1) * 5 != size)
		C[k] = arr[k * 5 + 1];
	int pivot = deterministic_selection(C, k + 1, (k + 1) / 2);
	int l = 0, r = size - 1;
	while (l <= r) {
		while (arr[l] < pivot) l++;
		while (arr[r] > pivot) r--;
		if (l <= r) std::swap(arr[l++], arr[r--]);
	}
	if (i == pivot)
		return l;
	else if (i < pivot)
		return deterministic_selection(arr, r + 1, i);
	else
		return deterministic_selection(arr + l, size - l, i);
}

/*
int main() {
	int n;
	std::cin >> n;

	int a[100];
	for (int i = 0; i < n; i++)
		std::cin >> a[i];

	int k;
	std::cin >> k;

	std::cout << deterministic_selection(a, n, k) << std::endl;

	return 0;
}
*/