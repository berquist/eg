#include <stdio.h>
#include <curand_kernel.h>
#include <curand.h>

// Adapted from
// https://stackoverflow.com/questions/26650391/generate-random-number-within-a-function-with-curand-without-preallocation
__global__ void myfunc(double *vals, size_t n) {
    int tId = threadIdx.x + (blockIdx.x * blockDim.x);
    curandState state;
    curand_init((unsigned long long)clock() + tId, 0, 0, &state);

    for (size_t i = 0; i < n; i++) {
        vals[i] = curand_uniform_double(&state);
    }
}

// Adapted from
// https://stackoverflow.com/questions/7989039/use-of-cudamalloc-why-the-double-pointer
int main() {
    size_t n = 20;
    size_t num_bytes = n * sizeof(double);

    double *vals_host = 0;
    vals_host = (double*)malloc(num_bytes);
    double *vals_device = 0;
    cudaMalloc((void**)&vals_device, num_bytes);

    myfunc<<<1, 1>>>(vals_device, n);

    cudaMemcpy(vals_host, vals_device, num_bytes, cudaMemcpyDeviceToHost);

    for (size_t i = 0; i < n; i++) {
        printf("%d = %lf\n", i, vals_host[i]);
    }

    free(vals_host);
    cudaFree(vals_device);

    return 0;
}
