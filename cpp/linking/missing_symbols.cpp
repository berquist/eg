#include "missing_symbols.h"

int bar() {
    return 3;
}

int baz() {
    int f = foo();
    return 4;
}
