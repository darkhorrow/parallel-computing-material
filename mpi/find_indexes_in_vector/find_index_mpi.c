#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define arraySize 10000

int main(int argc, char **argv)
{
    int rank, size;
    int vector[arraySize];
    int k = 6;
    MPI_Status status;

    srand (50);

    for (int i = 0; i < arraySize; i++) {
        vector[i] = rand()%100;;
    }

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int count = (sizeof(vector) / sizeof(int)) / (size - 1);
    int lastElements = arraySize % count;
    


    if (rank == 0) {

        int index;
        int child[size-1];
        int countFinished = 0;

        for (int i = 0; i < size-1; i++) {
            child[i] = 0;
        }

        while(countFinished <= (size-1)) {

            for (int i = 0; i < size-1; i++) {

                if (!child[i]) {
                    MPI_Recv(&index, 1, MPI_INT, i+1, 0, MPI_COMM_WORLD, &status);
                    
                }
                     
                if (index == -1) {
                    child[i] = 1;
                    countFinished++;
                } else {
                    printf("Soy el hilo %d y he recibido del hilo %d el indice %d \n", rank,  status.MPI_SOURCE, index);
                }

                
            }
        }

        
         

    } else {

        int finished = -1;

        if (rank < (size -1)) {

            for(int i = count*(rank-1); i < count*(rank-1)+count; i++) {
                if (vector[i] == k) {
                    MPI_Send(&i,1,MPI_INT,0,0,MPI_COMM_WORLD);
                }

            }

            MPI_Send(&finished,1,MPI_INT,0,0,MPI_COMM_WORLD);

        } else {

            for(int i = count*(rank-1); i < count*(rank-1)+count+lastElements; i++) {
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