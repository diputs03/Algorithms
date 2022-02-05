#include <iostream>
#include <string.h>

#define MAXN 2

int ret_matrix[MAXN][MAXN];

void matrix_add(int a[MAXN][MAXN], int b[MAXN][MAXN], int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			ret_matrix[i][j] = a[i][j] + b[i][j];
}

void matrix_minus(int a[MAXN][MAXN], int b[MAXN][MAXN], int n) {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			ret_matrix[i][j] = a[i][j] - b[i][j];
}

void matrix_mult(int x[MAXN][MAXN],  int y[MAXN][MAXN], int n) {
	if (n == 1) {
		ret_matrix[0][0] = x[0][0] * y[0][0];
		return;
	}

	int tmp1[MAXN][MAXN], tmp2[MAXN][MAXN];

	int A[MAXN][MAXN];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			A[i][j] = x[i][j];

	int B[MAXN][MAXN];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			B[i][j] = x[i][j + n / 2];

	int C[MAXN][MAXN];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			C[i][j] = x[i + n / 2][j];

	int D[MAXN][MAXN];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			D[i][j] = x[i + n / 2][j + n / 2];

	
	int E[MAXN][MAXN];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			E[i][j] = y[i][j];

	int F[MAXN][MAXN];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			F[i][j] = y[i][j + n / 2];

	int G[MAXN][MAXN];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			G[i][j] = y[i + n / 2][j];

	int H[MAXN][MAXN];
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			H[i][j] = y[i + n / 2][j + n / 2];


	int p1[MAXN][MAXN];
	matrix_minus(F, H, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			p1[i][j] = ret_matrix[i][j], ret_matrix[i][j] = 0;
	matrix_mult(p1, A, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			p1[i][j] = ret_matrix[i][j], ret_matrix[i][j] = 0;

	int p2[MAXN][MAXN];
	matrix_add(A, B, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			p2[i][j] = ret_matrix[i][j], ret_matrix[i][j] = 0;
	matrix_mult(p2, H, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			p2[i][j] = ret_matrix[i][j], ret_matrix[i][j] = 0;

	int p3[MAXN][MAXN];
	matrix_add(C, D, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			p3[i][j] = ret_matrix[i][j], ret_matrix[i][j] = 0;
	matrix_mult(p3, E, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			p3[i][j] = ret_matrix[i][j], ret_matrix[i][j] = 0;

	int p4[MAXN][MAXN];
	matrix_minus(G, E, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			p4[i][j] = ret_matrix[i][j], ret_matrix[i][j] = 0;
	matrix_mult(p4, D, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			p4[i][j] = ret_matrix[i][j], ret_matrix[i][j] = 0;

	int p5[MAXN][MAXN];
	matrix_add(A, D, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			tmp1[i][j] = ret_matrix[i][j], ret_matrix[i][j] = 0;
	matrix_add(E, H, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			tmp2[i][j] = ret_matrix[i][j], ret_matrix[i][j] = 0;
	matrix_mult(tmp1, tmp2, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			p5[i][j] = ret_matrix[i][j], ret_matrix[i][j] = 0;

	int p6[MAXN][MAXN];
	matrix_minus(B, D, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			tmp1[i][j] = ret_matrix[i][j], ret_matrix[i][j] = 0;
	matrix_add(G, H, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			tmp2[i][j] = ret_matrix[i][j], ret_matrix[i][j] = 0;
	matrix_mult(tmp1, tmp2, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			p6[i][j] = ret_matrix[i][j], ret_matrix[i][j] = 0;

	int p7[MAXN][MAXN];
	matrix_minus(A, C, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			tmp1[i][j] = ret_matrix[i][j], ret_matrix[i][j] = 0;
	matrix_add(E, F, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			tmp2[i][j] = ret_matrix[i][j], ret_matrix[i][j] = 0;
	matrix_mult(tmp1, tmp2, n / 2);
	for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++)
			p7[i][j] = ret_matrix[i][j], ret_matrix[i][j] = 0;

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
	
}

/*
int main() {
	int n = 2;
	int a[MAXN][MAXN] = { 1, 2, 3, 4 };
	int b[MAXN][MAXN] = { 5, 6, 7, 8 };
	matrix_mult(a, b, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			std::cout << ret_matrix[i][j] << " ";
		std::cout << std::endl;
	}
	return 0;
}
*/