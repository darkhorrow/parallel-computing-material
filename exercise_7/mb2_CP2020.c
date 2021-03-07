// PRACTICA 7 - Computacion Paralela - Master SIANI
// Multiplicacion vector - matriz
// El objetivo es paralelizarlo con la API OpenMP
//
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Definicion de subrutina
// Operacion: a = b x c
// b: matrix m x n
// a,c: vectores 1 x n
void mxv(int m, int n, double *a, double *b, double *c);


void main() {
  // Variables del programa principal
  int i,j,k,n,m; 
  float tiempo_antes, tiempo_despues;
  double *c,*b,*a;
  int hilos[4]={1,2,4,8}; // hilos del programa paralelo
  long int Niteraciones=9e8;
  int N=1;

  // Cada iteracion del bucle for k utiliza un tamaño de matriz mayor y reduce el numero de repeticiones
  for( k=0 ; k<4 ; k++) {
    N=10*N;
    Niteraciones=Niteraciones/100;

    n=N;
    m=N;

    // reserva de memoria para b y c
    if((b=(double *)malloc(m*n*sizeof(double)))==NULL){
	perror("Error al reservar memoria para b");
	exit(EXIT_FAILURE);
    }
    if((c=(double *)malloc(n*sizeof(double)))==NULL){
	perror("Error al reservar memoria para c");
	exit(EXIT_FAILURE);
    }

    /* Inicializacion de la matriz b y el vector c */
    for (j=0; j<n; j++) c[j] = 2.0;
    for (i=0; i<m; i++) 
      for (j=0; j<n; j++) b[i*n + j] = i;

    // Cada iteracion del bucle for k paraleliza con distinto numero de hilos
    // k=0: 1 hilo: k=1: 2 hilos; k=2: 4 hilos; k=3: 8 hilos
    for( j=0 ; j<4 ; j++) {

      // omp_set_num_threads(hilos[j]);

      tiempo_antes = clock();

      // reserva de memoria para a
      if((a=(double *)malloc(m*sizeof(double)))==NULL){
	perror("Error al reservar memoria para a");
	exit(EXIT_FAILURE);
      }
      // calculo del producto matriz por vector
      for(i=0; i< Niteraciones; i++){
        mxv(m,n,a,b,c); 
      }
      free(a);

      tiempo_despues= clock();

      printf("Numero de hilos: %i", hilos[j]);
      printf("\tVolumen Datos = %8.4f MB, N = %6i ", (float)(N*N+2*N)/(1024.0*1024.0), N);
      printf("\tTiempo = %5.1f seg ", tiempo_despues - tiempo_antes);
      float Nd= (float)N;
      float Nditeraciones= (float)Niteraciones;
      float tiempo= tiempo_despues - tiempo_antes;
      printf("\tMFLOPs = %10.4f  \n", tiempo>0?(float)(2*Nd*Nd*Nditeraciones)/(1e6*tiempo):0);
    } // for j
    //liberacion del espacio reservado
    free(b),free(c);
  } // for k
}

// subrutina mxv
void mxv(int m, int n, double *a, double *b, double *c) {
   int i, j;

   for (i=0; i<m; i++) {
	a[i] = 0.0;
	for (j=0; j<n; j++) a[i] += b[i*n + j]*c[j];
   }
}

