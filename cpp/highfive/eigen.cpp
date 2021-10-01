#include <eigen3/Eigen/Eigen>
#include <highfive/H5File.hpp>

using namespace HighFive;

int main() {
    const std::string filename("eigen.h5");
    File file(filename, File::ReadWrite | File::Create | File::Truncate);

    const Eigen::MatrixXd m1 = Eigen::MatrixXd::Random(3, 3);
    const Eigen::MatrixXd m2 = Eigen::MatrixXd::Random(4, 4);
    const Eigen::MatrixXd m3 = Eigen::MatrixXd::Random(2, 2);
    std::cout << "m1" << std::endl;
    std::cout << m1 << std::endl;
    std::cout << "m2" << std::endl;
    std::cout << m2 << std::endl;
    std::cout << "m3" << std::endl;
    std::cout << m3 << std::endl;

    DataSet dset_m1 = file.createDataSet("m", m1);

    return 0;
}
