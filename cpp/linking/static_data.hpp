#ifndef STATIC_DATA_HPP
#define STATIC_DATA_HPP

#include <cstddef>

template<typename TD, typename TC>
struct entry {
    const char *key;
    const char *title;
};

namespace static_data {

// struct mystruct {
//     static const double myval;
// };
// struct fdiff: can_add_step<fdiff>, can_save, iterable, inner_class_of<schema_base> {
struct fdiff {
    static const entry<size_t, fdiff> ideriv;
};
// const double mystruct::myval = 42.35;
const entry<size_t, fdiff> fdiff::ideriv = {"ideriv", "ideriv"};
    
} // namespace static_data

#endif // STATIC_DATA_HPP
