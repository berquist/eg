// #include <array>
#include <iostream>

#include "xtensor/xarray.hpp"
#include "xtensor/xtensor.hpp"
#include "xtensor/xio.hpp"
#include "xtensor/xview.hpp"

// template <typename T, std::size_t N>
// std::ostream& operator<<(std::ostream& os, const std::array<T, N> a) {
//     for (const auto& element: a) {
//         os << element << " ";
//     }
//     os << std::endl;
//     return os;
// }

int main() {

    // xt::xarray<double> arr1
    //     {{1.0, 2.0, 3.0},
    //      {2.0, 5.0, 7.0},
    //      {2.0, 5.0, 7.0}};

    // xt::xarray<double> arr2
    //     {5.0, 6.0, 7.0};

    // xt::xarray<double> res = xt::view(arr1, 1) + arr2;

    // std::cout << res;

    const xt::xtensor<double, 4> r = xt::random::randn<double>({1, 2, 3, 4});
    const xt::xarray<double> ra = xt::random::randn<double>({2, 2, 2, 2});
    std::cout << r << std::endl;
    std::cout << ra << std::endl;

    const auto r_shape = r.shape();
    const auto ra_shape = ra.shape();
    const size_t r_ndim = r_shape.size();
    const size_t ra_ndim = ra_shape.size();
    std::cout << r_ndim << std::endl;
    std::cout << ra_ndim << std::endl;

    // for (const auto& dim: r_shape) {
    //     std::cout << dim << " ";
    // }
    // std::cout << std::endl;
    // for (const auto& dim: ra_shape) {
    //     std::cout << dim << " ";
    // }
    // std::cout << std::endl;

    // std::cout << r.shape() << std::endl;
    // std::cout << ra.shape() << std::endl;

    const auto mr = r * r;
    const auto mra = ra * ra;
    std::cout << mr << std::endl;
    std::cout << mra << std::endl;
    // can't be double
    const auto smr = xt::eval(xt::sum(mr));
    const auto smra = xt::eval(xt::sum(mra));
    std::cout << smr << std::endl;
    std::cout << xt::sum(r * r) << std::endl;
    std::cout << xt::sum(r) * xt::sum(r) << std::endl;
    std::cout << smra << std::endl;
    std::cout << xt::sum(ra * ra) << std::endl;
    std::cout << xt::sum(ra) * xt::sum(ra) << std::endl;

    // last index is fastest -> row-major storage
    for (auto it = r.begin(); it != r.end(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
