#include <stdio.h>
#include <gsl/gsl_sf_gamma.h>

int main() {
    printf("hello, world!\n");
    printf("%f\n", gsl_sf_gamma(1.0));
    printf("%f\n", gsl_sf_gamma(1.5));
    printf("%f\n", gsl_sf_gamma(2.0));
    printf("%f\n", gsl_sf_gamma(2.5));
    printf("%f\n", gsl_sf_gamma(3.0));
}
