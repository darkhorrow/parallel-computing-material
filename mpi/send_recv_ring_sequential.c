#include <stdio.h>
#include <stdlib.h>  
#include "mpi.h"

#define SIZE 4096

void init_vector(unsigned int size, double* vector) {
	for(int j = 0; j < size; j++) vector[j] = j;
} 

int main(int argc, char **argv )
{
  int rank, size;
  double vector[SIZE];
  MPI_Status status;
  
  MPI_Init( &argc, &argv );
  
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &size );
  
  int value = 0;

  if(argc > 0) {
    value = atoi(argv[1]);
  }

  init_vector(SIZE, vector);

  int prev = rank - 1;
  int next = rank + 1;

  if(rank == 0) prev = size - 1;
  if(rank == (size - 1)) next = 0;
  
  while (value > 0) {
    if (rank == 0) {
      MPI_Send( &vector, SIZE, MPI_DOUBLE, next, 0, MPI_COMM_WORLD );
      MPI_Recv( &vector, SIZE, MPI_DOUBLE, prev, 0, MPI_COMM_WORLD, &status );
    } else {
      MPI_Recv( &vector, SIZE, MPI_DOUBLE, prev, 0, MPI_COMM_WORLD, &status );
      MPI_Send( &vector, SIZE, MPI_DOUBLE, next, 0, MPI_COMM_WORLD );
    }
	
	value--;
    
    printf( "Process %d send the vector to %d\n", rank, next);
  }
  
  MPI_Finalize( );
  return 0;
}