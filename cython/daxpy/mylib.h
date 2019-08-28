#ifndef MYLIB_H_
#define MYLIB_H_

#include <stddef.h>

int add1(int x);

void daxpy(size_t n, double alpha, const double *x, double *y);

void dgemm(size_t n, size_t l, size_t m, const double *x, const double *y, double *z);

#endif /* MYLIB_H_ */
