#include "core.h"
#include <stdio.h>

int main() {
    const size_t len = 4;
    double * in = (double*)malloc(len * sizeof(double));
    double * out = (double*)malloc(len * sizeof(double));
    for (size_t i = 0; i < len; i++) {
        in[i] = i+1;
        printf("%zu: %lf\n", i, out[i]);
    }
    elem_exp(out, in, len);
    for (size_t i = 0; i < len; i++) {
        printf("%zu: %lf\n", i, out[i]);
    }
    free(out);
    free(in);
    return 0;
}
