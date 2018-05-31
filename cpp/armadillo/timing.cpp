#include <cstdio>
#include <iostream>
#include <armadillo>
#include "../timer.h"

int main() {

    const size_t dim_r = 10;
    const size_t dim_c = 3;
    const size_t n_elem = dim_r * dim_c;

    const uint64 n_iter = 1e8;

    arma::sword cv[n_elem];
    for (size_t i = 0; i < n_elem; i++)
        cv[i] = i + 1;

    arma::imat m(cv, dim_r, dim_c);
    m = m.t();
    // m.print("m");
    m.save("arma_sword_mat.dat", arma::arma_ascii);

    uint64 start;
    uint64 stop;
    uint64 elapsed;
    uint64 per;

    arma::ivec v3;
    start = GetTimeMs64();
    for (uint64 i = 0; i < n_iter; i++) {
        v3 = vectorise(m);
    }
    stop = GetTimeMs64();
    elapsed = stop - start;
    per = elapsed / n_iter;
    // v3.print("v");
    std::cout << "v3 (vectorise, declare outside): " << elapsed << std::endl;
    v3.save("arma_sword_vec.dat", arma::arma_ascii);

    start = GetTimeMs64();
    for (uint64 i = 0; i < n_iter; i++) {
        arma::ivec v1 = vectorise(m);
    }
    stop = GetTimeMs64();
    elapsed = stop - start;
    per = elapsed / n_iter;
    std::cout << "v1 (vectorise, declare inside): " << elapsed << std::endl;
    // bad scope
    // v1.print("v1");

    start = GetTimeMs64();
    for (uint64 i = 0; i < n_iter; i++) {
        const arma::ivec v2 = vectorise(m);
    }
    stop = GetTimeMs64();
    elapsed = stop - start;
    per = elapsed / n_iter;
    std::cout << "v2 (vectorise, declare inside const): " << elapsed << std::endl;

    arma::ivec v4;
    start = GetTimeMs64();
    for (uint64 i = 0; i < n_iter; i++) {
        v4 = arma::ivec(m.memptr(), n_elem, false, true);
    }
    stop = GetTimeMs64();
    elapsed = stop - start;
    per = elapsed / n_iter;
    // v4.print("v");
    std::cout << "v4: " << elapsed << std::endl;

    arma::ivec v5;
    start = GetTimeMs64();
    for (uint64 i = 0; i < n_iter; i++) {
        v5 = arma::ivec(m.memptr(), n_elem, false, false);
    }
    stop = GetTimeMs64();
    elapsed = stop - start;
    per = elapsed / n_iter;
    // v5.print("v");
    std::cout << "v5: " << elapsed << std::endl;

    start = GetTimeMs64();
    for (uint64 i = 0; i < n_iter; i++) {
        const arma::ivec v6(m.memptr(), n_elem, false, false);
    }
    stop = GetTimeMs64();
    elapsed = stop - start;
    per = elapsed / n_iter;
    // bad scope
    // v6.print("v");
    std::cout << "v6: " << elapsed << std::endl;

    arma::ivec v7(n_elem);
    start = GetTimeMs64();
    for (uint64 i = 0; i < n_iter; i++) {
        memcpy(v7.memptr(), m.memptr(), n_elem * sizeof(double));
    }
    stop = GetTimeMs64();
    elapsed = stop - start;
    per = elapsed / n_iter;
    // v7.print("v");
    std::cout << "v7 (memcpy): " << elapsed << std::endl;


    return 0;
}
