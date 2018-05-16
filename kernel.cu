#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#define N 4
#define INF 100000

__device__ int min(int a, int b) {
	int min;
	if (a < b) {
		min = a;
	}
	else {
		min = b;
	}
}

__global__ void RoyFloyd(int a[N][N], int k) {
	int i = blockDim.x * blockIdx.x + threadIdx.x;
	for (int j = 0; j < N; j++) {
		a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
	}
}

int main()
{
	size_t size = N * sizeof(float);

	int h_A[N][N] = { { INF, 1, INF, 0 },
	{ 4, 0, 1, INF },
	{ 1, 0, INF,0},
	{ INF, 1, 0, INF},
	{INF, 0, 0, INF}
	};

	float* d_A;
	cudaMalloc(&d_A, size);
	cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);

	int threadsPerBlock = 1;
	int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

	for (int k = 0; k < N; k++) {
		RoyFloyd<<<blocksPerGrid, threadsPerBlock>>>(d_A, N);
	}

	cudaMemcpy(h_A, d_A, size, cudaMemcpyDeviceToHost);

	cudaFree(d_A);
}