#include <complex.h>
#include <stdio.h>

int main() {
    /* Taken from
     * https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html#Complex-Number-Types */
    complex double z = 1.0 + 3.0*I;
    printf("Phase is %lf, modulus is %lf\n", carg(z), cabs(z));
    printf("Real part is %lf, imaginary part is %lf\n", creal(z), cimag(z));

    return 0;
}
