#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#define MASTER 0

const int INFINITY = 1000000;
int n;

void royFloyd(int local_mat[50][50], int n, int my_rank, int p, MPI_Comm comm);

int main(int argc, char* argv[]) {

	int local_mat[50][50];
	int numprocs, my_rank;
	int k, i, j, temp;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", local_mat[i][j]);
		}
	}

	MPI_Bcast(local_mat, 25, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Send(&a, 25, MPI_INT, 0, 0, MPI_COMM_WORLD);

	if (my_rank == 0) {
		for (k = 0; k < n; k++) {
			for (i = 0; i < n; i++) {
				MPI_Recv(&temp, 25, MPI_INT, k, 0, MPI_COMM_WORLD);
				for (j = 0; j < n; j++) {
					if (temp[i][j] > local_mat[i][j])
						local_mat[i][j] = temp[i][j];
				}
			}
		}
	}

	MPI_Finalize; 

}