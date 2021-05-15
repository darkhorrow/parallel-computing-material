#include <stdio.h>
#include <stdlib.h>  
#include "mpi.h"

#define SIZE 4096

void initialize_vector(unsigned int size, double* vector) {
	for(int j = 0; j < size; j++) vector[j] = j;
} 

int main(int argc, char **argv) {
  int size, rank, next, prev;
  double vector[SIZE];
  MPI_Request reqs[2];
  MPI_Status stats[2];

  int loops = 0;

  if(argc > 1) {
    loops = atoi(argv[1]);
  } else {
	printf("Provide the number of N loops: ./isend_irecv_ring N");
	  exit(1);
  }

  initialize_vector(SIZE, vector);
  
  MPI_Init(&argc,&argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  /* Se obtienen los rangos de los procesos predecesor y siguiente */
  prev = rank-1;
  next = rank+1;
  if (rank == 0)  prev = size - 1;
  if (rank == (size - 1))  next = 0;

  while (loops > 0) {

    /* Recibimos, sin bloquearnos, un dato del predecesor y otro del sucesor */
    MPI_Irecv(&vector, SIZE, MPI_INT, prev, 0, MPI_COMM_WORLD, &reqs[0]);

    /* Enviamos, sin bloquearnos, nuestro rango al predecesor y al sucesor */
    MPI_Isend(&vector, SIZE, MPI_INT, next, 0, MPI_COMM_WORLD, &reqs[1]);

    /* Esperamos aqui hasta que las 4 operaciones hayan terminado */
    MPI_Waitall(2, reqs, stats);

    /* Imprimimos los resultados */
    printf( "Process %d sent the vector to process %d\n", rank, next);

    loops--;

  }
  
  MPI_Finalize();
}
