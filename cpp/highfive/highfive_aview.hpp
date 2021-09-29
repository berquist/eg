#ifndef LIBSTORE_IMPL_HDF5_HIGHFIVE_AVIEW_H_
#define LIBSTORE_IMPL_HDF5_HIGHFIVE_AVIEW_H_

#include <highfive/H5File.hpp>
#include <libaview/tens.h>

// Because array_views and tensors are not containers themselves but views on
// top of contiguous pre-allocated data, the data converters here cannot
// automatically resize the container they're reading into.  It is the
// responsibility of the caller to do this, otherwise the underlying HDF5 with
// throw an error.  This isn't bad though, since users of the views are used
// to doing the allocation and wrapping dance themselves.

using namespace HighFive;

//// array_view

template <typename T>
struct details::inspector<libaview::array_view<T>> {
    using type = libaview::array_view<T>;
    using value_type = T;
    using base_type = typename details::inspector<value_type>::base_type;

    static const size_t ndim = 1;
    static const size_t recursive_ndim = ndim + inspector<value_type>::recursive_ndim;

    static std::array<size_t, recursive_ndim> getDimensions(const type &val) {
        std::array<size_t, recursive_ndim> sizes{val.size()};
        return sizes;
    }
};

template <typename T>
struct details::data_converter<libaview::array_view<T>> {
    using container_type = libaview::array_view<T>;
    using value_type = typename details::inspector<T>::base_type;

    inline data_converter(const DataSpace &space) {
        const std::vector<size_t> dims = space.getDimensions();
        assert(dims.size() == 1);
    }

    inline const value_type * transform_write(const container_type &container) noexcept {
        return container.begin();
    }

    inline value_type * transform_read(container_type &container) {
        return container.begin();
    }

    inline void process_result(container_type &container) const noexcept { }
};

//// array_view

template <typename T>
struct details::inspector<libaview::tens2<T>> {
    using type = libaview::tens2<T>;
    using value_type = T;
    using base_type = typename details::inspector<value_type>::base_type;

    static const size_t ndim = 2;
    static const size_t recursive_ndim = ndim + inspector<value_type>::recursive_ndim;

    static std::array<size_t, recursive_ndim> getDimensions(const type &val) {
        std::array<size_t, recursive_ndim> sizes{val.dim_size(0), val.dim_size(1)};
        return sizes;
    }
};

template <typename T>
struct details::data_converter<libaview::tens2<T>> {
    using container_type = libaview::tens2<T>;
    using value_type = typename details::inspector<T>::base_type;

    inline data_converter(const DataSpace &space) {
        const std::vector<size_t> dims = space.getDimensions();
        assert(dims.size() == 2);
    }

    inline const value_type * transform_write(const container_type &container) noexcept {
        return container.view(0).begin();
    }

    inline value_type * transform_read(container_type &container) {
        return container.view(0).begin();
    }

    inline void process_result(container_type &container) const noexcept { }
};

//// tens3

template <typename T>
struct details::inspector<libaview::tens3<T>> {
    using type = libaview::tens3<T>;
    using value_type = T;
    using base_type = typename details::inspector<value_type>::base_type;

    static const size_t ndim = 3;
    static const size_t recursive_ndim = ndim + inspector<value_type>::recursive_ndim;

    static std::array<size_t, recursive_ndim> getDimensions(const type &val) {
        std::array<size_t, recursive_ndim> sizes{val.dim_size(0), val.dim_size(1), val.dim_size(2)};
        return sizes;
    }
};


template <typename T>
struct details::data_converter<libaview::tens3<T>> {
    using container_type = libaview::tens3<T>;
    using value_type = typename details::inspector<T>::base_type;

    inline data_converter(const DataSpace &space) {
        const std::vector<size_t> dims = space.getDimensions();
        assert(dims.size() == 3);
    }

    inline const value_type * transform_write(const container_type &container) noexcept {
        return container.view(0).begin();
    }

    inline value_type * transform_read(container_type &container) {
        return container.view(0).begin();
    }

    inline void process_result(container_type &container) const noexcept { }
};

//// tens4

template <typename T>
struct details::inspector<libaview::tens4<T>> {
    using type = libaview::tens4<T>;
    using value_type = T;
    using base_type = typename details::inspector<value_type>::base_type;

    static const size_t ndim = 4;
    static const size_t recursive_ndim = ndim + inspector<value_type>::recursive_ndim;

    static std::array<size_t, recursive_ndim> getDimensions(const type &val) {
        std::array<size_t, recursive_ndim> sizes{val.dim_size(0), val.dim_size(1), val.dim_size(2), val.dim_size(3)};
        return sizes;
    }
};

template <typename T>
struct details::data_converter<libaview::tens4<T>> {
    using container_type = libaview::tens4<T>;
    using value_type = typename details::inspector<T>::base_type;

    inline data_converter(const DataSpace &space) {
        const std::vector<size_t> dims = space.getDimensions();
        assert(dims.size() == 4);
    }

    inline const value_type * transform_write(const container_type &container) noexcept {
        return container.view(0).begin();
    }

    inline value_type * transform_read(container_type &container) {
        return container.view(0).begin();
    }

    inline void process_result(container_type &container) const noexcept { }
};


//// tens5

template <typename T>
struct details::inspector<libaview::tens5<T>> {
    using type = libaview::tens5<T>;
    using value_type = T;
    using base_type = typename details::inspector<value_type>::base_type;

    static const size_t ndim = 5;
    static const size_t recursive_ndim = ndim + inspector<value_type>::recursive_ndim;

    static std::array<size_t, recursive_ndim> getDimensions(const type &val) {
        std::array<size_t, recursive_ndim> sizes{val.dim_size(0), val.dim_size(1), val.dim_size(2), val.dim_size(3), val.dim_size(4)};
        return sizes;
    }
};

template <typename T>
struct details::data_converter<libaview::tens5<T>> {
    using container_type = libaview::tens5<T>;
    using value_type = typename details::inspector<T>::base_type;

    inline data_converter(const DataSpace &space) {
        const std::vector<size_t> dims = space.getDimensions();
        assert(dims.size() == 5);
    }

    inline const value_type * transform_write(const container_type &container) noexcept {
        return container.view(0).begin();
    }

    inline value_type * transform_read(container_type &container) {
        return container.view(0).begin();
    }

    inline void process_result(container_type &container) const noexcept { }
};


//// tens6

template <typename T>
struct details::inspector<libaview::tens6<T>> {
    using type = libaview::tens6<T>;
    using value_type = T;
    using base_type = typename details::inspector<value_type>::base_type;

    static const size_t ndim = 6;
    static const size_t recursive_ndim = ndim + inspector<value_type>::recursive_ndim;

    static std::array<size_t, recursive_ndim> getDimensions(const type &val) {
        std::array<size_t, recursive_ndim> sizes{val.dim_size(0), val.dim_size(1), val.dim_size(2), val.dim_size(3), val.dim_size(4), val.dim_size(5)};
        return sizes;
    }
};


template <typename T>
struct details::data_converter<libaview::tens6<T>> {
    using container_type = libaview::tens6<T>;
    using value_type = typename details::inspector<T>::base_type;

    inline data_converter(const DataSpace &space) {
        const std::vector<size_t> dims = space.getDimensions();
        assert(dims.size() == 6);
    }

    inline const value_type * transform_write(const container_type &container) noexcept {
        return container.view(0).begin();
    }

    inline value_type * transform_read(container_type &container) {
        return container.view(0).begin();
    }

    inline void process_result(container_type &container) const noexcept { }
};


#endif // LIBSTORE_IMPL_HDF5_HIGHFIVE_AVIEW_H_
