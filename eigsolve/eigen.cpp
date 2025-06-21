#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <iostream>

// https://stackoverflow.com/q/56323727
int main() {
    Eigen::Matrix3d m(3, 3);
    // Eigen::EigenSolver<Eigen::Matrix3f> es;
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> es;
    m(0, 0) = -0.386087;
    m(1, 1) = -0.390147;
    m(2, 2) = 0.776234;
    m(0, 1) = 0.00813956;
    m(0, 2) = 0.0781361;
    m(1, 0) = 0.0781361;
    m(1, 2) = 0.0986476;
    m(2, 0) = 0.0781361;
    m(2, 1) = 0.0986476;
    es.compute(m);
    std::cout << "matrix is:\n" << m << "\n"
              << "The eigenvalues of A are:\n" << es.eigenvalues() << "\n"
              << "The eigenvalues of A are:\n" << es.eigenvectors() << std::endl;
}
