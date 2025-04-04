#include <stdio.h>
#include <math.h>

int main() {
    const double d = 4.29;
    const int i = (int)d;
    const int i2 = d;
    const int ifl = (int)floor(d);
    const int ifl2 = floor(d);
    printf("%lf\n", d);
    printf("%lf %d\n", i, i);
    printf("%lf %d\n", i2, i2);
    printf("%lf %d\n", ifl, ifl);
    printf("%lf %d\n", ifl2, ifl2);
}
