#ifndef _6116188_HPP
#define _6116188_HPP

// Doesn't work
// int i;
// Works
const int i = 42;
// Works
// static int i;
// Works
// static int i = 42;

// Obvious compiler problem
// static const int i;
// const int i = 42;

// Finally, this reproduces the problem
#if 0
struct foo {
    static const int i;
};
const int foo::i = 42;
#endif

// void printer();

#endif // _6116188_HPP
