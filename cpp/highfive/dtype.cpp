#include <highfive/H5File.hpp>

using namespace HighFive;

int main() {
    const std::string filename("dtype.h5");
    File file(filename, File::ReadWrite | File::Create | File::Truncate);

    const std::string hello("hello");
    DataSet dset = file.createDataSet("s", hello);
    DataType dtype = dset.getDataType();
    std::cout << dtype.string() << std::endl;
    std::cout << dtype.isFixedLenStr() << std::endl;
    std::cout << dtype.isVariableStr() << std::endl;

    DataSet dset_get = file.getDataSet("s");
    DataType dtype_get = dset_get.getDataType();
    std::cout << dtype_get.string() << std::endl;
    std::cout << dtype_get.isFixedLenStr() << std::endl;
    std::cout << dtype_get.isVariableStr() << std::endl;

    const std::string longer("this is a longer string");
    dset.write(longer);

    std::vector<std::string> fruit {
        "apple",
        "pear",
        "banana",
    };

    DataSet dset2 = file.createDataSet("s2", fruit);

    fruit.push_back("cherry");

    return 0;
}
