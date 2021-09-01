#include <highfive/H5File.hpp>
#include <armadillo>

using namespace HighFive;

//// Col<T>

template <typename T>
struct details::inspector<arma::Col<T>> {
    using type = arma::Col<T>;
    using value_type = T;
    using base_type = typename details::inspector<value_type>::base_type;

    static const size_t ndim = 2;
    static const size_t recursive_ndim = ndim + inspector<value_type>::recursive_ndim;

    static std::array<size_t, recursive_ndim> getDimensions(const type &val) {
        std::array<size_t, recursive_ndim> sizes{val.n_elem, 1};
        return sizes;
    }
};

template <typename T>
struct details::data_converter<arma::Col<T>>
    : public details::container_converter<arma::Col<T>> {

    using container_type = arma::Col<T>;
    using value_type = typename details::inspector<T>::base_type;

    inline data_converter(const DataSpace &space)
        : details::container_converter<container_type>(space), _space(space) {

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
struct details::inspector<arma::Row<T>> {
    using type = arma::Row<T>;
    using value_type = T;
    using base_type = typename details::inspector<value_type>::base_type;

    static const size_t ndim = 2;
    static const size_t recursive_ndim = ndim + inspector<value_type>::recursive_ndim;

    static std::array<size_t, recursive_ndim> getDimensions(const type &val) {
        std::array<size_t, recursive_ndim> sizes{1, val.n_elem};
        return sizes;
    }
};

template <typename T>
struct details::data_converter<arma::Row<T>>
    : public details::container_converter<arma::Row<T>> {

    using container_type = arma::Row<T>;
    using value_type = typename details::inspector<T>::base_type;

    inline data_converter(const DataSpace &space)
        : details::container_converter<container_type>(space), _space(space) {

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
struct details::inspector<arma::Mat<T>> {
    using type = arma::Mat<T>;
    using value_type = T;
    using base_type = typename details::inspector<value_type>::base_type;

    static const size_t ndim = 2;
    static const size_t recursive_ndim = ndim + inspector<value_type>::recursive_ndim;

    static std::array<size_t, recursive_ndim> getDimensions(const type &val) {
        std::array<size_t, recursive_ndim> sizes{val.n_rows, val.n_cols};
        return sizes;
    }
};

template <typename T>
struct details::data_converter<arma::Mat<T>>
    : public details::container_converter<arma::Mat<T>> {

    using container_type = arma::Mat<T>;
    using value_type = typename details::inspector<T>::base_type;

    inline data_converter(const DataSpace &space)
        : details::container_converter<container_type>(space), _space(space) {

        const std::vector<size_t> dims = _space.getDimensions();
        assert(dims.size() == 2);
    }

    inline value_type * transform_read(container_type &container) {
        const std::vector<size_t> dims = _space.getDimensions();
        container.set_size(dims[0], dims[1]);
        return container.memptr();
    }

    inline const value_type * transform_write(const container_type &container) const noexcept {
        return container.memptr();
    }

    const DataSpace& _space;
};

//// Cube<T>

template <typename T>
struct details::inspector<arma::Cube<T>> {
    using type = arma::Cube<T>;
    using value_type = T;
    using base_type = typename details::inspector<value_type>::base_type;

    static const size_t ndim = 3;
    static const size_t recursive_ndim = ndim + inspector<value_type>::recursive_ndim;

    static std::array<size_t, recursive_ndim> getDimensions(const type &val) {
        std::array<size_t, recursive_ndim> sizes{val.n_rows, val.n_cols, val.n_slices};
        return sizes;
    }
};

template <typename T>
struct details::data_converter<arma::Cube<T>>
    : public details::container_converter<arma::Cube<T>> {

    using container_type = arma::Cube<T>;
    using value_type = typename details::inspector<T>::base_type;

    inline data_converter(const DataSpace &space)
        : details::container_converter<container_type>(space), _space(space) {

        const std::vector<size_t> dims = _space.getDimensions();
        assert(dims.size() == 3);
    }

    inline value_type * transform_read(container_type &container) {
        const std::vector<size_t> dims = _space.getDimensions();
        container.set_size(dims[0], dims[1], dims[2]);
        return container.memptr();
    }

    inline const value_type * transform_write(const container_type &container) const noexcept {
        return container.memptr();
    }

    const DataSpace& _space;
};
