#include "test-cxx/include/wrapper.hpp"

std::unique_ptr<Dummy> make_new_dummy() {
    return std::make_unique<Dummy>();
}
