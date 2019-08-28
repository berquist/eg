cdef extern from "mylib.h":
    int add1(int x)
    void daxpy(size_t n, double alpha, const double* x, double y)
    void dgemm(size_t n, size_t l, size_t m, const double* x, const double* y, double* z)
