#include <complex.h>
#include <stdio.h>

int main() {
    /* Taken from
     * https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html#Complex-Number-Types */
    complex double z = 1.0 + 3.0*I; 
    printf("Phase is %f, modulus is %f\n", carg(z), cabs(z));        

    return 0;
}
