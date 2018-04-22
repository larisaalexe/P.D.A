#include <stdio.h>
#include <stdlib.h>
#include <random>
#include "mpi.h"


#define MASTER 0
#define N 10


int main(int argc, char *argv[])
{
	int numprocs, procid, x, proc;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &procid);
	bool processLider = false;

	x = rand();

	for (proc = 0; proc < numprocs; proc++) {

		if (proc == numprocs)
			MPI_Send(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);

		else
			MPI_Send(&x, 1, MPI_INT, proc + 1, 0, MPI_COMM_WORLD);

		int number;
		
		if (proc == 0) {
			MPI_Recv(&number, 1, MPI_INT, numprocs, 0, MPI_COMM_WORLD, &status);
		}
		else {
			MPI_Recv(&number, 1, MPI_INT, proc - 1, 0, MPI_COMM_WORLD, &status);

		}

		if (number < x) {
			processLider = true;
			printf("Process %d is master /n", procid);
		}
			

	}



	MPI_Finalize();
}