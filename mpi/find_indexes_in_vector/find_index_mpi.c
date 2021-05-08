#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define MESSAGE_SIZE 10000
#define k 6

int main(int argc, char **argv)
{
    int rank, size;
    int vector[MESSAGE_SIZE];
    MPI_Status status;

    srand (50);

    for (int i = 0; i < MESSAGE_SIZE; i++) {
        vector[i] = rand()%100;;
    }

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int sizePerProcess = (sizeof(vector) / sizeof(int)) / (size - 1);
    int unmatchedElements = MESSAGE_SIZE % sizePerProcess;

    if (rank == 0) {
        int index;
        int process[size-1];
        int processFinished = 0;

        for (int i = 0; i < size-1; i++) {
            process[i] = 0;
        }

        while(processFinished <= (size-1)) {

            for (int i = 0; i < size-1; i++) {

                if (!process[i]) {
                    MPI_Recv(&index, 1, MPI_INT, i+1, 0, MPI_COMM_WORLD, &status);
                    
                }
                     
                if (index == -1) {
                    process[i] = 1;
                    processFinished++;
                } else {
                    printf("The master process (%d) received from %d de index %d \n", rank, status.MPI_SOURCE, index);
                }

                
            }
        }
    } else {
        int finished = -1;

        if (rank < (size -1)) {
            for(int i = sizePerProcess*(rank-1); i < sizePerProcess*(rank-1)+sizePerProcess; i++) {
                if (vector[i] == k) {
                    MPI_Send(&i,1,MPI_INT,0,0,MPI_COMM_WORLD);
                }

            }
            MPI_Send(&finished,1,MPI_INT,0,0,MPI_COMM_WORLD);
        } else {
            for(int i = sizePerProcess*(rank-1); i < sizePerProcess*(rank-1)+sizePerProcess+unmatchedElements; i++) {
                if (vector[i] == k) {
                    MPI_Send(&i,1,MPI_INT,0,0,MPI_COMM_WORLD);
                }

            }
            MPI_Send(&finished,1,MPI_INT,0,0,MPI_COMM_WORLD);
        }
    }

    MPI_Finalize( );

    return 0;
}