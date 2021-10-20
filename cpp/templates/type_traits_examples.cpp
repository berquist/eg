#include <type_traits>
#include <complex>
#include <vector>
#include <armadillo>

// This trick taken from https://stackoverflow.com/a/41495065.

template <typename>
struct is_arma_container_t : public std::false_type
{ };

template <typename T>
struct is_arma_container_t<arma::Row<T>> : public std::true_type
{ };

template <typename T>
struct is_arma_container_t<arma::Col<T>> : public std::true_type
{ };

template <typename T>
struct is_arma_container_t<arma::Mat<T>> : public std::true_type
{ };

template <typename T>
struct is_arma_container_t<arma::Cube<T>> : public std::true_type
{ };

template <typename T>
constexpr bool is_arma_container(T const &) {
    return is_arma_container_t<T>::value;
}

int main() {
    arma::mat mydmat;
    arma::cube mydcube;
    arma::Col<std::complex<double>> mycdcol;
    std::vector<double> mystldvec;
    double myd;

    std::cout << is_arma_container(mydmat) << std::endl;
    std::cout << is_arma_container(mydcube) << std::endl;
    std::cout << is_arma_container(mycdcol) << std::endl;
    std::cout << is_arma_container(mystldvec) << std::endl;
    std::cout << is_arma_container(myd) << std::endl;
    
    return 0;
}
