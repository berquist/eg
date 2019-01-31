#include <iostream>
#include <vector>
#include "xtensor/xarray.hpp"
#include "xtensor/xadapt.hpp"

int main() {

    const size_t len = 4;
    std::vector<int> v = {4, 2, 9, 6};
    // std::cout << v << std::endl;
    int * pv = &v[0];

    // https://stackoverflow.com/a/52745886
    std::vector<int> vpv(pv, pv + len);
    for (auto const& element : vpv) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    // xt::xarray<int> xv1(vpv);
    // std::cout << xv1 << std::endl;

    // https://stackoverflow.com/a/52849926
    // For a 1D tensor for instance
    xt::static_shape<std::size_t, 1> sh = {len};
    // Parameters of adapt are:
    // - the 1D buffer to adapt
    // - the size of the buffer
    // - the ownership flag (should the adaptor destroy your buffer upon deletion, here
    //   probably not)
    // - the shape
    auto a = xt::adapt(pv, len, false, sh);
    // std::cout << a << std::endl;

    return 0;
}
