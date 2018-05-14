#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 16

typedef struct {
	int width;
	int height;
	float* elements;
} Matrix;

int min(int a, int b) {
	return a > b ? a : b;
}

int main() {
	__global__void MatRoyFloydKernel(Matrix A, Matrix B, Matrix C) {
		int row = blockIdx.y * blockDim.y + threadIdx.y;
		int col = blockIdx.x * blockDim.x + threadIdx.x;
	}

	for (k = 0; k < n; k++) {
		MatRoyFloydKernel();
			for (i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					a[i][j] = min(a[i][j], a[i][k] + a[k][j];
				}

			}
	}
}
