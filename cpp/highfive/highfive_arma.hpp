#ifndef LIBSTORE_IMPL_HDF5_HIGHFIVE_ARMA_H_
#define LIBSTORE_IMPL_HDF5_HIGHFIVE_ARMA_H_

#include <highfive/H5File.hpp>
#include <armadillo>

namespace HighFive {
namespace details {

//// Col<T>

template <typename T>
struct inspector<arma::Col<T>> {
    using type = arma::Col<T>;
    using value_type = T;
    using base_type = typename inspector<value_type>::base_type;

    static const size_t ndim = 2;
    static const size_t recursive_ndim = ndim + inspector<value_type>::recursive_ndim;

    static std::array<size_t, recursive_ndim> getDimensions(const type &val) {
        std::array<size_t, recursive_ndim> sizes{val.n_elem, 1};
        return sizes;
    }
};

template <typename T>
struct data_converter<arma::Col<T>>
    : public container_converter<arma::Col<T>> {

    using container_type = arma::Col<T>;
    using value_type = typename inspector<T>::base_type;

    inline data_converter(const DataSpace &space)
        : container_converter<container_type>(space), _space(space) {

        const std::vector<size_t> dims = _space.getDimensions();
        assert(dims.size() == 2);
        assert(dims[1] == 1);
    }

    inline value_type * transform_read(container_type &container) {
        const std::vector<size_t> dims = _space.getDimensions();
        container.set_size(dims[0]);
        return container.memptr();
    }

    inline const value_type * transform_write(const container_type &container) const noexcept {
        return container.memptr();
    }

    const DataSpace& _space;
};

//// Row<T>

template <typename T>
struct inspector<arma::Row<T>> {
    using type = arma::Row<T>;
    using value_type = T;
    using base_type = typename inspector<value_type>::base_type;

    static const size_t ndim = 2;
    static const size_t recursive_ndim = ndim + inspector<value_type>::recursive_ndim;

    static std::array<size_t, recursive_ndim> getDimensions(const type &val) {
        std::array<size_t, recursive_ndim> sizes{1, val.n_elem};
        return sizes;
    }
};

template <typename T>
struct data_converter<arma::Row<T>>
    : public container_converter<arma::Row<T>> {

    using container_type = arma::Row<T>;
    using value_type = typename inspector<T>::base_type;

    inline data_converter(const DataSpace &space)
        : container_converter<container_type>(space), _space(space) {

        const std::vector<size_t> dims = _space.getDimensions();
        assert(dims.size() == 2);
        assert(dims[0] == 1);
    }

    inline value_type * transform_read(container_type &container) {
        const std::vector<size_t> dims = _space.getDimensions();
        container.set_size(dims[1]);
        return container.memptr();
    }

    inline const value_type * transform_write(const container_type &container) const noexcept {
        return container.memptr();
    }

    const DataSpace& _space;
};

//// Mat<T>

template <typename T>
struct inspector<arma::Mat<T>> {
    using type = arma::Mat<T>;
    using value_type = T;
    using base_type = typename inspector<value_type>::base_type;

    static const size_t ndim = 2;
    static const size_t recursive_ndim = ndim + inspector<value_type>::recursive_ndim;

    static std::array<size_t, recursive_ndim> getDimensions(const type &val) {
        std::array<size_t, recursive_ndim> sizes{val.n_rows, val.n_cols};
        return sizes;
    }
};

template <typename T>
struct data_converter<arma::Mat<T>> {

    using container_type = arma::Mat<T>;
    using value_type = typename inspector<T>::base_type;

    inline data_converter(const DataSpace &space)
        : _space(space) {

        const std::vector<size_t> dims = _space.getDimensions();
        assert(dims.size() == 2);
    }

    inline value_type * transform_read(container_type &container) {
        const std::vector<size_t> dims = _space.getDimensions();
        container.set_size(dims[1], dims[0]);
        return container.memptr();
    }

    inline const value_type * transform_write(const container_type &container) noexcept {
        // This is to write out in row-major order and get the data to
        // live long enough.
        _container_st = container_type(container.st());
        return _container_st.memptr();
    }

    inline void process_result(container_type &container) {
        container = container_type(container.st());
    }

    const DataSpace& _space;
    container_type _container_st;
};

//// Cube<T>

template <typename T>
struct inspector<arma::Cube<T>> {
    using type = arma::Cube<T>;
    using value_type = T;
    using base_type = typename inspector<value_type>::base_type;

    static const size_t ndim = 3;
    static const size_t recursive_ndim = ndim + inspector<value_type>::recursive_ndim;

    static std::array<size_t, recursive_ndim> getDimensions(const type &val) {
        std::array<size_t, recursive_ndim> sizes{val.n_slices, val.n_rows, val.n_cols};
        return sizes;
    }
};

template <typename T>
struct data_converter<arma::Cube<T>> {

    using container_type = arma::Cube<T>;
    using value_type = typename inspector<T>::base_type;

    inline data_converter(const DataSpace &space)
        : _space(space) {

        const std::vector<size_t> dims = _space.getDimensions();
        assert(dims.size() == 3);
    }

    inline value_type * transform_read(container_type &container) {
        const std::vector<size_t> dims = _space.getDimensions();
        // The row/col dims need to be flipped here, but the actual data will
        // be flipped in process_result.  We can't do it here because the read
        // happens in row-major order.
        container.set_size(dims[2], dims[1], dims[0]);
        return container.memptr();
    }

    inline const value_type * transform_write(const container_type &container) noexcept {
        _buffer.resize(container.n_elem);
        size_t offset;
        for (size_t k = 0; k < container.n_slices; k++) {
            for (size_t j = 0; j < container.n_cols; j++) {
                for (size_t i = 0; i < container.n_rows; i++) {
                    // Transpose row and column indices
                    offset = j + (container.n_cols * i) + (container.n_rows * container.n_cols * k);
                    _buffer[offset] = container(i, j, k);
                }
            }
        }
        return _buffer.data();
    }

    inline void process_result(container_type &container) noexcept {
        arma::Cube<value_type> ret(container.n_cols, container.n_rows, container.n_slices);
        for (size_t k = 0; k < container.n_slices; k++) {
            ret.slice(k) = container.slice(k).st();
        }
        container = ret;
    }

    const DataSpace& _space;
    std::vector<value_type> _buffer;
};

} // end namespace details
} // end namespace HighFive

#endif // LIBSTORE_IMPL_HDF5_HIGHFIVE_ARMA_H_
