#include <stdio.h> 

#include <sys/time.h>

double getTime(void) {
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    return tv.tv_sec + 1e-6*(double)tv.tv_usec;
}

#define NBIN 1000000000 // Number of bins
// #define NUM_BLOCK 500 // Number of thread blocks (max 2^32-1)
// #define NUM_THREAD 64 // Number of threads per block (max 1024)



__global__ void cal_pi(
    double *sum, int nbin, double step) {
    int i;
    double x;
    int idx = blockIdx.x*blockDim.x+threadIdx.x;
    for (i=idx; i< nbin; i+= blockDim.x*gridDim.x) {
        x = (i+0.5)*step;
        sum[idx] += 4.0/(1.0+x*x);
    }
}




int main(void) {
    int  blocks[8] = {60,120,180,240,300,360,430,600}; //here we define an array of blocks
    int  threads[10] = {16,32,48,64,80,96,112,128,144,160}; //here we define an array of threads
    int NUM_BLOCK,NUM_THREAD;

    for (int i=0;i<8;i++) for (int j=0;j<10;j++){ //we loop over all the combinations in blocks and threads arrays
        NUM_BLOCK = blocks[i];
        NUM_THREAD = threads[j];
        
        dim3 dimGrid(NUM_BLOCK,1,1); // Grid dimensions
        dim3 dimBlock(NUM_THREAD,1,1); // Block dimensions
        double *sumHost, *sumDev; // Pointer to host & device arrays
        double pi = 0;
        int tid;
        double step = 1.0/NBIN; // Step size
        size_t size = NUM_BLOCK*NUM_THREAD*sizeof(double);
        sumHost = (double *)malloc(size); // array on host
        cudaMalloc((void **) &sumDev, size);// array on GPU
        cudaMemset(sumDev, 0, size); // Zero results array

        double start, end;
        start = getTime();
        cal_pi <<<dimGrid, dimBlock>>>(sumDev,NBIN,step); // call CUDA kernel
        // Retrieve result from device and store it in host array
        cudaMemcpy(sumHost, sumDev, size, cudaMemcpyDeviceToHost);
        for(tid=0; tid<NUM_THREAD*NUM_BLOCK; tid++)
        pi += sumHost[tid];
        pi *= step;
        // Cleanup
        end=getTime();
        double delta = end - start;
        printf("NUM_BLOCK: %d, NUM_THREAD: %d -> PI = %.16g computed in %.4g seconds\n", NUM_BLOCK, NUM_THREAD, pi, delta);
        free(sumHost);
        cudaFree(sumDev);
    }
}
