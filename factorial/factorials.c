#include <stdio.h>

int factorial_int(int n) {
    if (n == 0) {
        return 1;
    }
    return n * factorial_int(n - 1);
}

unsigned factorial_unsigned(int n) {
    if (n == 0) {
        return 1;
    }
    return n * factorial_unsigned(n - 1);
}

long factorial_long(long n) {
    if (n == 0) {
        return 1;
    }
    return n * factorial_long(n - 1);
}

long long factorial_long_long(long long n) {
    if (n == 0) {
        return 1;
    }
    return n * factorial_long_long(n - 1);    
}

unsigned long long factorial_unsigned_long_long(unsigned long long n) {
    if (n == 0) {
        return 1;
    }
    return n * factorial_unsigned_long_long(n - 1);    
}

int main() {
    for (unsigned long long i = 0; i < 25; i++) {
        printf("%3llu %13d %13u %25ld %25lld %25llu\n",
               i,
               factorial_int(i),
               factorial_unsigned(i),
               factorial_long(i),
               factorial_long_long(i),
               factorial_unsigned_long_long(i));
    }
    return 0;
}
