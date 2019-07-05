#include <stddef.h>

int add1(int x) {
    return x + 1;
}

/*
  daxpy compute y := alpha * x + y where alpha is a scalar and x and y are
  n-vectors.
*/

void daxpy(size_t n, double alpha, const double *x, double *y) {
    for (size_t i = 0; i < n; i++) {
        y[i] += alpha * x[i];
    }
}
