#include <iostream> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>

#define MAXN 100

using namespace std;

int ret_mult[MAXN];

int mult(int* X, int X_size, int* Y, int Y_size) {

	memset(ret_mult, 0, sizeof(ret_mult));

	if (min(X_size, Y_size) == 1) {
		int* Z;
		int Z_size, fact;
		if (X_size == 1) Z = Y, Z_size = Y_size, fact = X[0];
		else Z = X, Z_size = X_size, fact = Y[0];

		for (int i = 0; i < Z_size; i++) {
			ret_mult[i] += fact * Z[i];
			ret_mult[i + 1] = ret_mult[i] / 10;
			ret_mult[i] %= 10;
		}
		return Z_size + (ret_mult[Z_size] + 9) / 10;

	}

	int XY_cut = min(X_size, Y_size) / 2;

	int* A = X + XY_cut;
	int* B = X;
	int* C = Y + XY_cut;
	int* D = Y;


	int A_size, B_size;
	int C_size, D_size;

	A_size = X_size - XY_cut;
	B_size = XY_cut;
	C_size = Y_size - XY_cut;
	D_size = XY_cut;
	
	int AC[MAXN], BD[MAXN], ABCD[MAXN];

	int AC_size = mult(A, A_size, C, C_size);
	for (int i = 0; i < AC_size; i++)
		AC[i] = ret_mult[i];

	int BD_size = mult(B, B_size, D, D_size);
	for (int i = 0; i < BD_size; i++)
		BD[i] = ret_mult[i];

	int AB_sum[MAXN], CD_sum[MAXN];

	int i;
	AB_sum[0] = 0;
	for (i = 0; i < max(A_size, B_size); i++) {
		if (i < A_size)
			AB_sum[i] += A[i];
		if (i < B_size)
			AB_sum[i] += B[i];
		AB_sum[i + 1] = AB_sum[i] / 10;
		AB_sum[i] %= 10;
	}
	int AB_sum_size = max(A_size, B_size) + AB_sum[i];

	CD_sum[0] = 0;
	for (i = 0; i < max(C_size, D_size); i++) {
		if (i < C_size)
			CD_sum[i] += C[i];
		if (i < D_size)
			CD_sum[i] += D[i];
		CD_sum[i + 1] = CD_sum[i] / 10;
		CD_sum[i] %= 10;
	}
	int CD_sum_size = max(C_size, D_size) + CD_sum[i];

	int ABCD_size = mult(AB_sum, AB_sum_size, CD_sum, CD_sum_size);
	for (i = 0; i < ABCD_size; i++)
		ABCD[i] = ret_mult[i];

	int subt = 0;
	for (i = 0; i < ABCD_size; i++) {
		ABCD[i] -= subt;
		if (i < AC_size)
			ABCD[i] -= AC[i];
		if (i < BD_size)
			ABCD[i] -= BD[i];
		subt = 0;
		while (ABCD[i] < 0) subt++, ABCD[i] += 10;
	}
	while (!ABCD[--i]);
	ABCD_size = ++i;

	memset(ret_mult, 0, sizeof(ret_mult));
	ret_mult[0] = 0;
	for (i = 0; i < X_size + Y_size; i++) {
		if (BD_size > i)
			ret_mult[i] += BD[i];
		if (i >= XY_cut && i < ABCD_size + XY_cut)
			ret_mult[i] += ABCD[i - XY_cut];
		if (i >= 2 * XY_cut && i < AC_size + 2 * XY_cut)
			ret_mult[i] += AC[i - 2 * XY_cut];
		ret_mult[i + 1] = ret_mult[i] / 10;
		ret_mult[i] %= 10;
	}
	return X_size + Y_size - (int)!ret_mult[i - 1];
}

/*
int a[MAXN];
char k[MAXN] = "3141592653589793238462643383279502884197169399375105820974944592";
int b[MAXN];
char p[MAXN] = "2718281828459045235360287471352662497757247093699959574966967627";
int main() {
	int a_size = 64, b_size = 64;
	for (int i = 0; i < a_size; i++) {
		a[i] = k[a_size - i - 1] - '0';
	}
	for (int i = 0; i < b_size; i++) {
		b[i] = p[b_size - i - 1] - '0';
	}
	int di = mult(a, a_size, b, b_size);
	for (int i = 0; i < di; i++)
		cout << ret_mult[i];
	return 0;
}
*/