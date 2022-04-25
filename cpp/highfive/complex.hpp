#ifndef COMPLEX_HPP_
#define COMPLEX_HPP_

#include <highfive/H5DataSpace.hpp>

namespace HighFive {
namespace details {

template <typename Scalar>
struct data_converter<std::complex<Scalar>, void> {
    inline data_converter(const DataSpace&) noexcept {
        static_assert(std::is_arithmetic<Scalar>::value,
                      "inner datatype for complex should be an arithmetic value");
    }

    inline std::complex<Scalar>* transform_read(std::complex<Scalar>& datamem) const noexcept {
        return &datamem;
    }

    inline const std::complex<Scalar>* transform_write(const std::complex<Scalar>& datamem) const noexcept {
        return &datamem;
    }

    inline void process_result(std::complex<Scalar>&) const noexcept {}
};

} // namespace details
} // namespace HighFive

#endif // COMPLEX_HPP_
