#include <iostream>
#include <algorithm>
#include <cmath>
#include <string.h>

int ret_merge[100000];

void merge(const int a[], const int size1, const int b[], const int size2) {
	for (int i = 0, j = 0, k = 0; k < size1 + size2; k++)
		if ((a[i] < b[j] && i < size1) || !(j < size2))
			ret_merge[k] = a[i++];
		else
			ret_merge[k] = b[j++];
}

void merge_sort(int arr[], const int size) {
	if (size == 1) return;
	merge_sort(arr, size / 2);
	merge_sort(arr + size / 2, (size + 1) / 2);
	merge(arr, size / 2, arr + size / 2, (size + 1) / 2);
	for (int i = 0; i < size; i++)
		arr[i] = ret_merge[i];
}

int c[100000];

/*
int main() {
	int n;
	std::cin >> n;

	for (int i = 0; i < n; i++)
		std::cin >> c[i];

	merge_sort(c, n);

	for (int i = 0; i < n; i++)
		std::cout << c[i] << " ";

	std::cout << std::endl;
	return 0;
}
*/