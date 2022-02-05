#include <iostream>
#include <math.h>
#include <algorithm>

void quick_sort(int arr[], int size) {
	if (size == 0) return;
	int l = 0, r = size - 1;
	srand(time(NULL));
	int pivot = arr[rand() % size];
	while (l <= r) {
		while (arr[l] < pivot) l++;
		while (arr[r] > pivot) r--;
		if (l <= r) std::swap(arr[l++], arr[r--]);
	}
	quick_sort(arr, r + 1);
	quick_sort(arr + l, size - l);
}

/*
int main() {
	int n;
	std::cin >> n;
	int arr[100];
	for (int i = 0; i < n; i++)
		std::cin >> arr[i];

	quick_sort(arr, n);

	for (int i = 0; i < n; i++)
		std::cout << arr[i] << " ";

	std::cout << std::endl;
	return 0;
}
*/