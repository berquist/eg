#ifndef _DUMMY_HPP
#define _DUMMY_HPP

struct Dummy {
    int x;
    char y;
};

std::unique_ptr<Dummy> make_dummy();

#endif // _DUMMY_HPP
