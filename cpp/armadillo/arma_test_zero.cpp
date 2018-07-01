#include <armadillo>
#include <cassert>
#include <cstdio>

int main() {

    size_t zero = 0;

    arma::vec Av(zero);
    arma::mat Am(zero, zero);
    arma::cube Ac(zero, zero, zero);

    Av.print("Av");
    printf("%p\n", &Av);
    Am.print("Am");
    printf("%p\n", &Am);
    Ac.print("Ac");
    printf("%p\n", &Ac);

    arma::cube Bc = 2.0 * Ac;

    Bc.print("Bc");
    printf("%p\n", &Bc);

    arma::cube Cc = Ac + 1.2;

    Cc.print("Cc");
    printf("%p\n", &Cc);

    arma::cube Dc(zero, 2, zero);
    arma::cube Ec(2, 2, zero);

    Dc.print("Dc");
    printf("%p\n", &Dc);
    Ec.print("Ec");
    printf("%p\n", &Ec);

    int d_Ec_Dc = &Dc - &Ec;
    printf("d_Ec_Dc: %d\n", d_Ec_Dc);
    assert(d_Ec_Dc == 1);
    int d_Ec_Bc = &Bc - &Ec;
    printf("d_Ec_Bc: %d\n", d_Ec_Bc);
    // int d_Av_Dc = &Dc(0, 0, 0) - &Av(0);
    // printf("d_Av_Dc: %d\n", d_Av_Dc);

    Av.zeros();
    Am.zeros();
    Ac.zeros();
    Ec.zeros();

    return 0;

}
