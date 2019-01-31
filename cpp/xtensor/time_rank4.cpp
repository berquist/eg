#include <iostream>
#include <chrono>

#include "xtensor/xtensor.hpp"
#include "xtensor/xrandom.hpp"
// #include "xtensor/xio.hpp"

int main() {

    const size_t dim = 1e6;
    const xt::xtensor<double, 1> rt = xt::random::randn<double>({dim});

    const size_t nruns = 20;
    std::vector<long long> times(nruns);
    std::chrono::high_resolution_clock::time_point ts, te;
    for (size_t run = 0; run < nruns; run++) {
        ts = std::chrono::high_resolution_clock::now();
        // const auto rdot = xt::linalg::dot(rt, rt);
        const auto&& rdot_simple = xt::eval(xt::sum(rt * rt));
        // std::cout << rdot_simple << std::endl;
        // std::cout << xt::eval(rdot_simple) << std::endl;
        // std::cout << xt::sum(rt * rt) << std::endl;
        te = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(te - ts).count();        
        std::cout << run << " (ms): " << duration << std::endl;
        times[run] = duration;
    }
    xt::xtensor<long long, 1> xtimes = times;
    std::cout << xtimes << std::endl;
    // std::cout << "total time (ms): " << ttime << std::endl;
    // std::cout << "average time (ms): " << static_cast<double>(ttime) / nruns << std::endl;

    return 0;
}
