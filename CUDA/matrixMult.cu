#include <stdio.h>
#include <stdlib.h> 
#include <cuda_runtime.h>

__global__ void matrixMult(double *a, double *b, double *c, int n) {
    int col = blockIdx.x*blockDim.x + threadIdx.x;
    int row = blockIdx.y*blockDim.y + threadIdx.y;

    if (row < n && col < n) {
        for (int i = 0; i < n; ++i) {
            c[row*n + col] += a[row*n + i] * b[i*n + col];
        }
    }
}

int main(int argc, char* argv) {
    int N = 320;
    int size = N*N; // Matrix size
	int blocksPerGrid = 32; // Blocks per CUDA grid

    double *a, *b, *c;          // Host copies of matrix a, b, c
    double *d_a, *d_b, *d_c;    // Device copies of a, b, c

    // Alloc memory in host for double array
    a = (double*) malloc(size*sizeof(double));
    b = (double*) malloc(size*sizeof(double));
    c = (double*) malloc(size*sizeof(double));
    
    // Init a simple matrix in vector format
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            a[i*N + j] = i*N + j;
            b[i*N + j] = i*N + j;
        }
    }

    // Alloc memory in device for double array
    cudaMalloc(&d_a, size*sizeof(double)); 
    cudaMalloc(&d_b, size*sizeof(double));
    cudaMalloc(&d_c, size*sizeof(double));

    // Copy from host to device
    cudaMemcpy(d_a, a, size*sizeof(double),cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size*sizeof(double),cudaMemcpyHostToDevice);

    
    // Nº of threads and blocks to use
    dim3 blocksPerGrid( blocksPerGrid, blocksPerGrid);
    dim3 threadsPerBlock( N / blocksPerGrid, N / blocksPerGrid);

    cudaEvent_t start, stop;
    float elapsedTime;

	// Start recording time elapsed
    cudaEventCreate(&start);
    cudaEventRecord(start,0);

	// Launch kernel
    matrixMult<<<blocksPerGrid,threadsPerBlock>>>(d_a,d_b,d_c,N);
	
	// Wait until the kernel has finished its execution
    cudaDeviceSynchronize();

	// Stop recording time elapsed
    cudaEventCreate(&stop);
    cudaEventRecord(stop,0);
    cudaEventSynchronize(stop);

    cudaEventElapsedTime(&elapsedTime, start,stop);
    printf("Elapsed time : %f ms\n" ,elapsedTime);

    // Copy from device to host the result
    cudaMemcpy(c, d_c, size*sizeof(double), cudaMemcpyDeviceToHost);


	// Uncomment this block to visualize the result
	
	/*
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            printf("%f \t", c[i*N + j]);
        }
        printf("\n");
    }
	*/

    // Free memory used in both host and device
    free(a); free(b); free(c);
    cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);

    printf("Done\n");
    return 0;
}

