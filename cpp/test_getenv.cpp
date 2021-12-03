#include <iostream>

int main() {
    const char * path_p = getenv("PATH");
    if (path_p == NULL) {
        throw std::runtime_error("getting PATH failed");
    }
    const std::string path_s(path_p);
    std::cout << path_s << std::endl;

    return 0;
}
