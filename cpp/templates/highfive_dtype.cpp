// #include <armadillo>
#include "type_name.hpp"
#include "dtype_utils.h"

using namespace HighFive;

std::ostream& operator<<(std::ostream &os, const DataTypeClass &dtc) {
    os << type_class_string(dtc);
    return os;
}

std::ostream& operator<<(std::ostream &os, const DataType &dt) {
    os << dt.string();
    return os;
}

int main() {
    std::vector<double> mydvec;
    std::vector< std::complex<double> > mycdvec;
    // auto dtype_d = get_dtype(mydvec);
    // auto dtype_cd = get_dtype(mycdvec);
    // std::cout << "dtype_d: " << dtype_d << std::endl;
    // std::cout << "dtype_cd: " << dtype_cd << std::endl;

    std::cout << type_name< inner_type<decltype(mydvec)> >() << std::endl;
    std::cout << type_name< inner_type<decltype(mycdvec)> >() << std::endl;
}
