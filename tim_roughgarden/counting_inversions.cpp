#include <iostream>

int ret_inv[100];

//merge the array too
int count_split_inv(int arr1[], int size1, int arr2[], int size2) {
	int count = 0;
	for (int i = 0, j = 0, k = 0; k < size1 + size2; k++)
		if (!(i < size1))
			ret_inv[k] = arr2[j++];
		else if (arr1[i] < arr2[j] || !(j < size2))
			ret_inv[k] = arr1[i++];
		else
			ret_inv[k] = arr2[j++], count++;
	return count;
}

//sort the array too
int count_inv(int arr[], int size) {
	if (size == 1) return 0;
	int x = count_inv(arr, size / 2);
	int y = count_inv(arr + size / 2, (size + 1) / 2);
	int z = count_split_inv(arr, size / 2, arr + size / 2, (size + 1) / 2);
	for (int i = 0; i < size; i++)
		arr[i] = ret_inv[i];
	return x + y + z;
}

/*
int main() {
	int a[5] = { 5, 1, 2, 3, 4 };
	std::cout << count_inv(a, 5) << std::endl;
	return 0;
}
*/