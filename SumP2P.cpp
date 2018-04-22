#include "mpi.h"
#include <stdio.h>
#include <math.h>


#define MAXSIZE 100
#define N 5 


int main(int argc, char **argv)
{
	int myid, numprocs;
	int  i, x, low, high, myresult = 0, result;
	int v[N];

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	if (0 == myid) {
		for ( i = 0; i < N; i++) {
			v[i] = v[i] + 1;
		}
	}
	/* broadcast data */
	MPI_Bcast(v, MAXSIZE, MPI_INT, 0, MPI_COMM_WORLD);
	/* add portion of data */
	x = MAXSIZE / numprocs; /* must be an integer */
	low = myid * x;
	high = low + x;
	for (i = low; i<high; i++) {
		myresult += v[i];
	}
	printf("I got %d from %d\n", myresult, myid);
	/* compute global sum */
	MPI_Reduce(&myresult, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	if (0 == myid) {
		printf("The sum is %d.\n", result);
	}
	MPI_Finalize();
}