#ifndef _DUMMY_HPP
#define _DUMMY_HPP

#include <memory>

struct Dummy {
    int x;
    char y;
};

std::unique_ptr<Dummy> make_dummy();

#endif // _DUMMY_HPP
