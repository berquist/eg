#include <armadillo>
#include <cassert>
#include <cstdio>
#include <iostream>

int main() {

    // arma::arma_rng::set_seed_random();
    arma::arma_rng::set_seed(5489);

    arma::cube Ac(2, 2, 2, arma::fill::randn);

    Ac.print("Ac");
    printf("%p\n", &Ac);

    Ac.save("Ac_arma_ascii.armamat", arma::arma_ascii);
    // Ac.save("Ac_arma_raw_ascii.armamat", arma::raw_ascii);

    // This doesn't work, because the save() method uses a differerent
    // stream!

    // std::cout.precision(16);

    // Ac.save("Ac_arma_ascii_16.armamat", arma::arma_ascii);
    // Ac.save("Ac_arma_raw_ascii_16.armamat", arma::raw_ascii);

    // std::ofstream ofs("Ac_arma_ascii_16.armamat", std::ofstream::trunc);
    std::ofstream ofs("Ac_arma_ascii_16.armamat", std::ios::out | std::ios::binary | std::ios::trunc);
    ofs.precision(16);
    // ofs << 16.972 << std::endl;
    // ofs << std::setprecision(16) << 16.972 << std::endl;
    Ac.save(ofs, arma::arma_binary);
    ofs.close();

    return 0;

}
