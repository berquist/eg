#include <iostream>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &v) {
    os << "[ ";
    for (size_t i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }
    os << "]";
    return os;
}

int main() {
    std::vector<int> v1 {4, 2, 9, 10, 11};
    std::cout << v1 << std::endl;
    auto it = v1.erase(v1.end() - 2);
    std::cout << v1 << std::endl;

    return 0;
}
