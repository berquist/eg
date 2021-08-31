#include <h5cpp/hdf5.hpp>

using namespace hdf5;

int main() {
    const file::File file = file::create("string.h5", file::AccessFlags::TRUNCATE);
    const node::Group root = file.root();

    const auto dtype_string = datatype::create<std::string>();

    const std::string mystring("I am just a string");

    const auto dset_string = node::Dataset(root, "s1", dtype_string);
    dset_string.write(mystring);

    return 0;
}
