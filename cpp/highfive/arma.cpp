#include "highfive_arma.hpp"
#include "interface.hpp"

using namespace HighFive;

template<typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); i++) {
        os << "v[" << i << "] = " << v[i] << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream &os, const ObjectType &ot) {
    switch (ot) {
    case ObjectType::File:
        os << "ObjectType::File";
        break;
    case ObjectType::Group:
        os << "ObjectType::Group";
        break;
    case ObjectType::UserDataType:
        os << "ObjectType::UserDataType";
        break;
    case ObjectType::DataSpace:
        os << "ObjectType::DataSpace";
        break;
    case ObjectType::Dataset:
        os << "ObjectType::Dataset";
        break;
    case ObjectType::Attribute:
        os << "ObjectType::Attribute";
        break;
    case ObjectType::Other:
        os << "ObjectType::Other";
        break;
    default:
        throw std::invalid_argument("invalid argument to operator<< for HighFive::ObjectType");
    }
    return os;
}

int main() {
    const std::string filename("arma.h5");
    File file(filename, File::ReadWrite | File::Create | File::Truncate);

    Interface iface(filename);

    const size_t dim_big = 20;
    const arma::Col<double> rv1(dim_big, arma::fill::randn);
    const arma::mat rm1(dim_big, dim_big, arma::fill::randn);
    const arma::Cube<double> rc1(2, 3, 4, arma::fill::randn);
    const arma::Cube<arma::sword> rc2(2, 3, 4, arma::fill::zeros);

    rv1.print("rv1");
    auto dset_rv1 = file.createDataSet("rv1", rv1);
    arma::Col<double> rv1_read;
    rv1_read.print("rv1_read (before)");
    dset_rv1.read(rv1_read);
    rv1_read.print("rv1_read (after)");

    // Make a DataSet just from a DataSpace, *then* write.
    DataSpace dspace_rv1 = DataSpace::From(rv1);
    // std::cout << dspace_rv1 << std::endl;
    DataSet dset_rv1_clone = file.createDataSet<double>("rv1_clone", dspace_rv1);
    dset_rv1_clone.write(rv1);
    arma::Col<double> rv1_read_clone;
    dset_rv1_clone.read(rv1_read_clone);

    const arma::Col<double> rv2(dim_big, arma::fill::randn);
    rv2.print("rv2");
    dset_rv1_clone.write(rv2);

    iface.write("/vecs/rv2", rv2);

    arma::Col<double> rv3;
    iface.read("/vecs/rv2", rv3);
    rv3.print("rv3 (that is rv2)");

    iface.write("/vecs/rv4", arma::Col<double>(3, arma::fill::randn));
    iface.write("/cubes/rc3", arma::cube(2, 3, 4, arma::fill::randn));

    arma::cube rc3;
    iface.read("/cubes/rc3", rc3);
    rc3.print("rc3 (read)");

    arma::imat rm2 = arma::randi<arma::imat>(6, 7, arma::distr_param(-10, +20));
    iface.write("/mats/rm2", rm2);
    iface.write("/nested/mats/rm2", rm2);

    const std::string mystring("I am just a string");
    iface.write("/strings/s1", mystring);
    std::string mynewstring;
    iface.read("/strings/s1", mynewstring);
    std::cout << mynewstring << std::endl;

    const double n1_ = 1.23;
    const int n2_ = 4;
    const size_t n3_ = size_t(4);
    iface.write("/nums/n1", n1_);
    iface.write("/nums/n2", n2_);
    iface.write("/nums/n3", n3_);
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

    std::cout << iface.get_paths() << std::endl;

    return 0;
}
