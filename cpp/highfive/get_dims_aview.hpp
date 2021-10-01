#ifndef GET_DIMS_AVIEW_HPP_
#define GET_DIMS_AVIEW_HPP_

#include <vector>

#include <libaview/tens.h>

template <typename T>
std::vector<std::size_t> get_dims(const libaview::array_view<T> &value) {
    return {value.size()};
}

template <typename T>
std::vector<std::size_t> get_dims(const libaview::tens2<T> &value) {
    return {value.dim_size(0), value.dim_size(1)};
}

template <typename T>
std::vector<std::size_t> get_dims(const libaview::tens3<T> &value) {
    return {value.dim_size(0), value.dim_size(1), value.dim_size(2)};
}

template <typename T>
std::vector<std::size_t> get_dims(const libaview::tens4<T> &value) {
    return {value.dim_size(0), value.dim_size(1), value.dim_size(2), value.dim_size(3)};
}

template <typename T>
std::vector<std::size_t> get_dims(const libaview::tens5<T> &value) {
    return {value.dim_size(0), value.dim_size(1), value.dim_size(2), value.dim_size(3), value.dim_size(4)};
}

template <typename T>
std::vector<std::size_t> get_dims(const libaview::tens6<T> &value) {
    return {value.dim_size(0), value.dim_size(1), value.dim_size(2), value.dim_size(3), value.dim_size(4), value.dim_size(5)};
}

#endif // GET_DIMS_AVIEW_HPP_
