#include <iostream>

#include <Eigen/CXX11/Tensor>

int main() {

    // Map a tensor of ints on top of stack-allocated storage.
    // 2 x 4 x 2 x 8
    int storage[128];
    // Eigen::TensorMap<int, 4> t_4d(storage, 2, 4, 2, 8);

    // The same storage can be viewed as a different tensor. You can
    // also pass the sizes as an array.
    // Eigen::TensorMap<int, 2> t_2d(storage, 16, 8);

    return 0;
}
