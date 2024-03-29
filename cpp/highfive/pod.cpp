#include "common.hpp"
#include "interface.hpp"
#include <highfive/H5DataType.hpp>
#include "complex.hpp"

using namespace HighFive;

int main() {
    const std::string filename("pod.h5");
    File file(filename, File::ReadWrite | File::Create | File::Truncate);

    Interface iface(filename);

    const std::string mystring("I am just a string");
    iface.write("/strings/s1", mystring);
    std::string mynewstring;
    iface.read("/strings/s1", mynewstring);
    std::cout << mynewstring << std::endl;

    const double n1_ = 1.23;
    const int n2_ = 4;
    const size_t n3_ = size_t(4);
    const std::complex<double> n4_ {2.0, 3.2};
    iface.write("/nums/n1", n1_);
    iface.write("/nums/n2", n2_);
    iface.write("/nums/n3", n3_);
    iface.write("/nums/n4", n4_);
    // DataSet dset_double = file.createDataSet("/nums/n1", 1.23);
    // DataSet dset_int = file.createDataSet("/nums/n2", 4);
    // DataSet dset_sizet = file.createDataSet("/nums/n3", size_t(4));
    double n1;
    int n2;
    size_t n3;
    iface.read("/nums/n1", n1);
    iface.read("/nums/n2", n2);
    iface.read("/nums/n3", n3);
    std::cout << "n1: " << n1 << std::endl;
    std::cout << "n2: " << n2 << std::endl;
    std::cout << "n3: " << n3 << std::endl;

    std::cout << file.listObjectNames() << std::endl;
    std::cout << "exist rv1: " << file.exist("rv1") << std::endl;
    std::cout << "exist /nums/n3: " << file.exist("/nums/n3") << std::endl;
    std::cout << "exist nums/n3: " << file.exist("nums/n3") << std::endl;

    const Group group_nums = file.getGroup("nums");
    std::cout << group_nums.getPath() << std::endl;
    const ObjectType type_nums = file.getObjectType("nums");
    std::cout << type_nums << std::endl;

    // Dimensions for scalars should all be empty.
    const DataSpace dspace_string = file.getDataSet("/strings/s1").getSpace();
    const DataSpace dspace_double = file.getDataSet("/nums/n1").getSpace();
    std::cout << "dspace_string.getDimensions: " << dspace_string.getDimensions() << std::endl;
    std::cout << "dspace_double.getDimensions: " << dspace_double.getDimensions() << std::endl;
    std::cout << "dspace_string.getMaxDimensions: " << dspace_string.getMaxDimensions() << std::endl;
    std::cout << "dspace_double.getMaxDimensions: " << dspace_double.getMaxDimensions() << std::endl;

    // auto dtype = create_and_check_datatype<std::complex<double>>();
    // auto dspace = DataSpace(1);
    // auto dset = file.createDataSet("/nums/n4", dspace, dtype);
    // dset.write(n4_);

    return 0;
}
