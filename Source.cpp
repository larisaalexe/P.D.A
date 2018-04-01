#include <stdio.h>
#include <stdlib.h>
#include <random>
#include "mpi.h"


#define MASTER 0
#define N 10
int main(int argc, char *argv[])
{
	int numprocs, procid, len, i, sum;
	int sum_all = 0;
	char hostname[MPI_MAX_PROCESSOR_NAME];
	int v[N];
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &procid);
	MPI_Get_processor_name(hostname, &len);
	printf("Hello from proc %d on %s!\n", procid, hostname);

	if (procid == MASTER)
		printf("MASTER: Number of MPI procs is: %d\n", numprocs);
	
	if (procid == MASTER) {
		for (i = 0; i < N; i++) {
			v[i] = rand();
		}
	}

	sum = 0;
	for (i = 0; i < N; i++)
		sum = sum + v[i];

	if (procid != MASTER) {
		MPI_Send(&sum, 1, MPI_INT, MASTER, 1, MPI_COMM_WORLD);
	}
	else{
		sum_all = sum;
		for (i = 1; i < numprocs; i++) {
			MPI_Recv(&sum, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
			sum_all = sum_all + sum;
		}
	}
	
	if (procid == MASTER) {
		printf("\n"); 
		for (i = 0; i < N; i++)
			printf("%d", v[i], " ");
		printf("\n");
		printf("Sum is : ");
		printf("%d", sum_all);
	}
	MPI_Finalize();
}