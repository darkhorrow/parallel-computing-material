#include <stdio.h>
#include <stdlib.h>  
#include "mpi.h"

#define charSize 32*2048

int main(int argc, char **argv) {

    int rank, size;
    double t1, t2, local_elapsed, elapsed;
    char message[charSize] = "";

    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Barrier(MPI_COMM_WORLD);
    t1 = MPI_Wtime();

    MPI_Bcast(&message, charSize, MPI_CHAR, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    t2 = MPI_Wtime();
    local_elapsed = t2 - t1;

    MPI_Reduce(&local_elapsed, &elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Transcurridos %f segundos\n",elapsed);
    }


    MPI_Finalize( );

    return 0;
}