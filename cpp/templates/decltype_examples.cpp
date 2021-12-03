#include <armadillo>
#include "type_name.hpp"


int main() {
    arma::mat mymat;
    std::cout << typeid(mymat).name() << std::endl;
    std::cout << type_name<decltype(mymat)>() << std::endl;;

    std::vector<double> mydvec;
    std::vector< std::complex<double> > mycdvec;
    std::cout << type_name<decltype(mydvec)>() << std::endl;;
    std::cout << type_name<decltype(mycdvec)>() << std::endl;;

    return 0;
}
