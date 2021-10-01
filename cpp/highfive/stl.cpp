#include <limits>
#include <random>

#include <highfive/H5File.hpp>

#include "common.hpp"

using namespace HighFive;

static std::vector<int> generate_data(size_t size) {
    using value_type = int;
    // We use static in order to instantiate the random engine
    // and the distribution once only.
    // It may provoke some thread-safety issues.
    static std::uniform_int_distribution<value_type> distribution(
        std::numeric_limits<value_type>::min(),
        std::numeric_limits<value_type>::max());
    static std::default_random_engine generator;

    std::vector<value_type> data(size);
    std::generate(data.begin(), data.end(), []() { return distribution(generator); });
    return data;
}

int main() {
    const std::string filename("stl.h5");
    File file(filename, File::ReadWrite | File::Create | File::Truncate);

    std::vector<int> v10 = generate_data(10);
    std::vector<int> v20 = generate_data(20);
    std::vector<int> v30 = generate_data(30);
    std::cout << "v10" << std::endl;
    std::cout << v10 << std::endl;
    std::cout << "v20" << std::endl;
    std::cout << v20 << std::endl;
    std::cout << "v30" << std::endl;
    std::cout << v30 << std::endl;

    DataSet dset_0 = file.createDataSet("v0", v20);

    std::string attr_0_contents("v20");
    Attribute attr_0 = dset_0.createAttribute<std::string>("contents", DataSpace::From(attr_0_contents));
    attr_0.write(attr_0_contents);

    DataSet dset_1 = file.createDataSet("v1", v20);
    dset_1.write(v10);

    std::string attr_1_contents("v10");
    Attribute attr_1 = dset_1.createAttribute<std::string>("contents", DataSpace::From(attr_1_contents));
    attr_1.write(attr_1_contents);

    DataSet dset_2 = file.createDataSet("v2", v20);
    dset_2.write(v30);

    std::string attr_2_contents("v30");
    Attribute attr_2 = dset_2.createAttribute<std::string>("contents", DataSpace::From(attr_2_contents));
    attr_2.write(attr_2_contents);

    DataSet dset_0_unlimited = file.createDataSet<int>("v0_unlimited", DataSpace(DataSpace::UNLIMITED));

    return 0;
}
