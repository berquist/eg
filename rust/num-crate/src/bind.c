#include <math.h>
#include <complex.h>

#define EPSILON_REF (double)pow(10, -62)

double errAbs(double complex ref, double complex comp) {
    double complex diff = ref - comp;
    double norm = (creal(diff) * creal(diff)) + (cimag(diff) * cimag(diff));
    return sqrt(norm);
}

double errRel(double complex ref, double complex comp) {
    double absRef = sqrt((creal(ref) * creal(ref)) + (cimag(ref) * cimag(ref)));
    if (absRef < EPSILON_REF) {
        return errAbs(ref, comp);
    }
    return errAbs(ref, comp) / absRef;
}
