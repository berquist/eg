#include <ostream>
#include <libint2/boys.h>

double boys_reference_single(double T, size_t m) {
    const auto instance = libint2::FmEval_Reference<double>();
    return instance.eval(T, m);
}

std::vector<double> boys_reference_multiple(double T, size_t max_m) {
    std::vector<double> ret(max_m + 1);
    const auto instance = libint2::FmEval_Reference<double>();
    instance.eval(ret.data(), T, max_m);
    return ret;
}

std::vector<double> boys_reference2(double T, size_t max_m) {
    std::vector<double> ret(max_m + 1);
    const auto instance = libint2::FmEval_Reference2<double>();
    instance.eval(ret.data(), T, max_m);
    return ret;
}

std::vector<double> boys_chebyshev7(double T, size_t max_m) {
    std::vector<double> ret(max_m + 1);
    const auto instance = libint2::FmEval_Chebyshev7<double>::instance(max_m);
    instance->eval(ret.data(), T, max_m);
    return ret;
}

std::vector<double> boys_taylor(double T, size_t max_m) {
    const auto instance = libint2::FmEval_Taylor<double>::instance(max_m);
    if (max_m > instance->max_m()) {
        throw std::invalid_argument(
            "trying to use higher max_m than interpolation order allows"
            );
    }
    std::vector<double> ret(max_m + 1);
    instance->eval(ret.data(), T, max_m);
    return ret;
}

template<typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); i++) {
        os << "v[" << i << "] = " << v[i] << std::endl;
    }
    return os;
}

int main() {
    const double T = 2.0;
    const size_t max_m = 2;
    std::cout << boys_reference_single(T, max_m) << std::endl;
    std::cout << boys_reference_multiple(T, max_m) << std::endl;
    std::cout << boys_reference2(T, max_m) << std::endl;
    std::cout << boys_chebyshev7(T, max_m) << std::endl;
    std::cout << boys_taylor(T, max_m) << std::endl;
    return 0;
}
