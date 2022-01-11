#include <cstddef>
#include <vector>

std::vector<double> return_by_value(size_t len) {
    std::vector<double> ret;
    for (size_t i = 0; i < len; i++) {
        ret.push_back(i * 1.0);
    }
    return ret;
}

// const std::vector<double>& return_by_const_reference(size_t len, std::vector<double> &ret) {
//     // std::vector<double> ret;
//     for (size_t i = 0; i < len; i++) {
//         ret.push_back(i * 1.0);
//     }
//     return ret;
// }

int main() {
    const auto len = 10;
    const auto v1 = return_by_value(len);
    // v2 = return_by_const_reference(len);
    return 0;
}
