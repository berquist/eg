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

void dgemm(size_t n, size_t l, size_t m, const double *x, const double *y, double *z) {
    /* Shapes: x is [n, m], y is [m, l], z is [n, l]

       A reminder that C is row-major, meaning the last (column) index is the
       fastest. So each time you move to a new row, you're offset by the
       number of columns.*/
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < l; j++) {
            for (size_t k = 0; k < m; k++) {
                z[(i * l) + j] = x[(i * m) + k] * y[(k * l) + j];
            }
        }
    }
}
