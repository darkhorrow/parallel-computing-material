#include <stdio.h>
#include <stdlib.h> 
#include <cuda_runtime.h>


__global__ void mult(double *a, double *b, double *result, int n) {

    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;

    if (row < n && col < n) {
        for (int i = 0; i < n; ++i) {
            result[row * n + col] += a[row * n + i] * b[i * n + col];
        }
    }

}



int main(void) {

    srand (1);
    int dimension = 320;
    int size = dimension*dimension;

    double *a, *b, *result;          // host copies of matrix a,b,result
    double *d_a, *d_b, *d_result;    // device copies of a,b,result

    // memoria host
    a = (double *)malloc(size*sizeof(double));
    b = (double *)malloc(size*sizeof(double));
    result = (double *)malloc(size*sizeof(double));
    
    // inicializamos matrices
    for(int i = 0; i < dimension; i++) {
        for(int j = 0; j < dimension; j++) {
            a[i*dimension+j] = i*dimension+j;
            b[i*dimension+j] = i*dimension+j;
            
        }
    }

    // memoria device
    cudaMalloc(&d_a, size*sizeof(double)); 
    cudaMalloc(&d_b, size*sizeof(double));
    cudaMalloc(&d_result, size*sizeof(double));

    // copiamos a device
    cudaMemcpy(d_a,a,size*sizeof(double),cudaMemcpyHostToDevice);
    cudaMemcpy(d_b,b,size*sizeof(double),cudaMemcpyHostToDevice);

    int blockSize = 32;
    // llamamos al kernel
    dim3 blocksPerGrid( blockSize, blockSize);
    dim3 threadsPerBlock( dimension / blockSize, dimension / blockSize);

    cudaEvent_t start, stop;
    float elapsedTime;

    cudaEventCreate(&start);
    cudaEventRecord(start,0);

    mult<<<blocksPerGrid,threadsPerBlock>>>(d_a,d_b,d_result,dimension);
    cudaDeviceSynchronize();

    cudaEventCreate(&stop);
    cudaEventRecord(stop,0);
    cudaEventSynchronize(stop);

    cudaEventElapsedTime(&elapsedTime, start,stop);
    printf("Elapsed time : %f ms\n" ,elapsedTime);

    // ???????????
    cudaMemcpy(result, d_result, size*sizeof(double), cudaMemcpyDeviceToHost);


    // for(int i = 0; i < dimension; i++) {
    //     for(int j = 0; j < dimension; j++) {
    //         printf("%f \t", result[i*dimension+j]);
    //     }
    //     printf("\n");
    // }

    // ????????
    free(a); free(b); free(result);
    cudaFree(d_a); cudaFree(d_b); cudaFree(d_result);

    printf("Done\n");
    return 0;
}

