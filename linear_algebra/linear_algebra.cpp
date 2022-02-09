#include <iostream>
#include <string.h>

int** matrix_add(int** a, int** b, int n) {
	int** ret = new int* [n];
	for (int i = 0; i < n; i++)
		ret[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			ret[i][j] = a[i][j] + b[i][j];
	return ret;
}

int** matrix_minus(int** a, int** b, int n) {
	int** ret = new int* [n];
	for (int i = 0; i < n; i++)
		ret[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			ret[i][j] = a[i][j] - b[i][j];
	return ret;
}

int** matrix_mult(int** x, int** y, int n) {
	if (n == 1) {
		int** mat = new int* [1];
		mat[0] = new int[1];
		mat[0][0] = x[0][0] * y[0][0];
		return mat;
	}

	int** tmp1, ** tmp2;
	int** A, ** B, ** C, ** D, ** E, ** F, ** G, ** H;

	A = x;
	B = &x[n / 2];
//	C = &(x[0][n / 2]);
	C = new int* [n / 2];
	for (int i = 0; i < n / 2; i++) {
		C[i] = new int[n / 2];
		for (int j = 0; j < n / 2; j++)
			C[i][j] = x[i + n / 2][j];
	}

//	D = &(x[n / 2][n / 2]);
	D = new int* [n / 2];
	for (int i = 0; i < n / 2; i++) {
		D[i] = new int[n / 2];
		for (int j = 0; j < n / 2; j++)
			D[i][j] = x[i + n / 2][j + n / 2];
	}
	E = y;
	F = &y[n / 2];
//	G = &(y[0][n / 2]);
	G = new int* [n / 2];
	for (int i = 0; i < n / 2; i++) {
		G[i] = new int[n / 2];
		for (int j = 0; j < n / 2; j++)
			G[i][j] = y[i + n / 2][j];
	}

//	H = &(y[n / 2][n / 2]);
	H = new int* [n / 2];
	for (int i = 0; i < n / 2; i++) {
		H[i] = new int[n / 2];
		for (int j = 0; j < n / 2; j++)
			H[i][j] = y[i + n / 2][j + n / 2];
	}

	int** p1;
	tmp1 = matrix_minus(F, H, n / 2);
	p1 = matrix_mult(tmp1, A, n / 2);
	delete[] tmp1;

	int** p2;
	tmp1 = matrix_add(A, B, n / 2);
	p2 = matrix_mult(tmp1, H, n / 2);
	delete[] tmp1;

	int** p3;
	tmp1 = matrix_add(C, D, n / 2);
	p3 = matrix_mult(tmp1, E, n / 2);
	delete[] tmp1;

	int** p4;
	tmp1 = matrix_minus(G, E, n / 2);
	p4 = matrix_mult(tmp1, D, n / 2);
	delete[] tmp1;

	int** p5;
	tmp1 = matrix_add(A, D, n / 2);
	tmp2 = matrix_add(E, H, n / 2);
	p5 = matrix_mult(tmp1, tmp2, n / 2);
	delete[] tmp1;
	delete[] tmp2;

	int** p6;
	tmp1 = matrix_minus(B, D, n / 2);
	tmp2 = matrix_add(G, H, n / 2);
	p6 = matrix_mult(tmp1, tmp2, n / 2);
	delete[] tmp1;
	delete[] tmp2;

	int** p7;
	tmp1 = matrix_minus(A, C, n / 2);
	tmp2 = matrix_add(E, F, n / 2);
	p7 = matrix_mult(tmp1, tmp2, n / 2);
	delete[] tmp1;
	delete[] tmp2;

	int** ret_matrix = new int* [n];
	for (int i = 0; i < n; i++)
		ret_matrix[i] = new int[n];

	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			ret_matrix[i][j] = p5[i][j] + p4[i][j] + p6[i][j] - p2[i][j];

	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			ret_matrix[i][j + n / 2] = p1[i][j] + p2[i][j];

	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			ret_matrix[i + n / 2][j] = p3[i][j] + p4[i][j];

	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			ret_matrix[i + n / 2][j + n / 2] = p1[i][j] + p5[i][j] - p3[i][j] - p7[i][j];
	return ret_matrix;
}

int** matrix_pow(int** mat, int pow, int n) {
	if (pow == 1)
		return mat;
	return (pow & 1) ? matrix_mult(matrix_pow(mat, pow / 2, n), mat, n) : matrix_pow(mat, pow / 2, n);
}

int** unint_matrix(int n) {
	int** ret = new int* [n];
	for (int i = 0; i < n; i++) {
		ret[i] = new int[n];
		for (int j = 0; j < n; j++)
			if (i == j)
				ret[i][j] = 1;
			else
				ret[i][j] = 0;
	}
	return ret;
}

int** matrix_inverse(int** mat, int n) {
	int** augumented = new int* [n];
	for (int i = 0; i < n; i++) {
		augumented[i] = new int[2 * n];
		for (int j = 0; j < n; j++)
			augumented[i][j] = mat[i][j];
		for (int j = n; j < 2 * n; j++)
			if (j == i + n)
				augumented[i][j] = 1;
			else
				augumented[i][j] = 0;
	}
	int head = 0;
	for (int i = 1; i < n; i++)
		for (int j = i; j < n; j++) {
			double fact = augumented[j][head] / augumented[i][head];
			for (int k = head; i < 2 * n; k++)
				augumented[j][k] -= augumented[i][k] * fact;
		}
	int** ans = new int* [n];
	for (int i = 0; i < n; i++) {
		ans[i] = new int[n];
		for (int j = 0; j < n; j++)
			ans[i][j] = augumented[i][j + n];
	}
	delete[] augumented;
	return ans;
}

int* Guassian_Elimination(int** mat, int n) {
	int head = 0;
	for (int i = 1; i < n; i++)
		for (int j = i; j < n; j++) {
			double fact = mat[j][head] / mat[i][head];
			for (int k = head; i < n + 1; k++)
				mat[j][k] -= mat[i][k] * fact;
		}
	int* ans = new int [n];
	for (int i = n - 1; i >= 0; i--) {
		int tmp = mat[i][n];
		for (int j = n - 1; j > i; j--)
			tmp -= mat[i][j] * ans[j];
		ans[i] = tmp / mat[i][i];
	}
	return ans;
}

//failure < 2 ^ -k
bool Freivalds(int** a, int** b, int** product, int n, int k) {
	srand(time(NULL));
	int* v = new int[n];
	while (k--) {
		for (int i = 0; i < n; i++)
			v[i] = rand() % 2;
		int* expected = new int[n];
		for (int i = 0; i < n; i++) {
			expected[i] = 0;
			for (int j = 0; j < n; j++)
				expected[i] += v[i] * product[i][j];
		}
		int* result = new int[n];
		for (int i = 0; i < n; i++) {
			result[i] = 0;
			for (int j = 0; j < n; j++)
				result[i] += v[i] * a[i][j];
			int tmp = 0;
			for (int j = 0; j < n; j++)
				tmp += result[i] * b[i][j];
			result[i] = tmp;
		}
		for (int i = 0; i < n; i++)
			if (result[i] != expected[i])
				return false;
	}
	return true;
}