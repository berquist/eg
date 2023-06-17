#ifndef _WRAPPER_HPP
#define _WRAPPER_HPP

#include <memory>

struct Dummy { int x; double y; };
std::unique_ptr<Dummy> make_new_dummy();

#endif // _WRAPPER_HPP
