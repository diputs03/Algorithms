#include <iostream>

//return ith smallest element
int randomized_selection(int arr[], int size, int i) {
	if (size == 1)
		return arr[0];
	int l = 0, r = size - 1;
	srand(time(NULL));
	int pivot = arr[rand() % size];
	while (l <= r) {
		while (arr[l] < pivot) l++;
		while (arr[r] > pivot) r--;
		if (l <= r) std::swap(arr[l++], arr[r--]);
	}
	if (i == pivot)
		return l;
	else if (i < pivot)
		return randomized_selection(arr, r + 1, i);
	else
		return randomized_selection(arr + l, size - l, i);
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

	std::cout << randomized_selection(a, n, k) << std::endl;

	return 0;
}
*/