#include <stdio.h>
#include <stdlib.h>
#include <random>
#include "mpi.h"


#define MASTER 0
#define N 10


int main(int argc, char *argv[])
{
	int numprocs, procid, i, sum, tempSum;
	int sum_all = 0;
	int v[N];
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &procid);
	

	//Master
	if (procid == MASTER) { 
		for (i = 0; i < N; i++) {
			v[i] = rand();
		}
		for (int proc = 0; proc < numprocs; proc++) {
			MPI_Send(v, N / numprocs, MPI_INT, procid, 1, MPI_COMM_WORLD);
		}

		for (int proc = 0; proc < numprocs; proc++) {
			MPI_Recv(&tempSum, 1, MPI_INT, procid, 1, MPI_COMM_WORLD, &status);
			sum_all = sum_all + tempSum;
		}

		printf("Sum of elements is :");
		printf("%d", sum_all);
	}
	//Slave
	else {
		int sum = 0;
		MPI_Recv(v, N / numprocs, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		for (i = 0; i < N / numprocs; i++) {
			sum = sum + v[i];
		}
		MPI_Send(&sum, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
	}
	MPI_Finalize();
}
