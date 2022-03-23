#ifndef ENABLE_IF_H
#define ENABLE_IF_H

#include <iostream>

// https://stackoverflow.com/q/15427667
template<typename T>
typename std::enable_if<!(std::is_same<T, int>::value || std::is_same<T, float>::value), void>::type myfunc() {
    std::cout << "default" << std::endl;
}

template<typename T>
typename std::enable_if<std::is_same<T, int>::value, void>::type myfunc() {
    std::cout << "int" << std::endl;
}

template<typename T>
typename std::enable_if<std::is_same<T, float>::value, void>::type myfunc() {
    std::cout << "float" << std::endl;
}

class myclass {
public:
    // You can't do this...
    // template<typename T>
    // void
    // mymethod();
    template<typename T>
    typename std::enable_if<!(std::is_same<T, float>::value || std::is_same<T, int>::value), void>::type
    mymethod();

    template<typename T>
    typename std::enable_if<std::is_same<T, float>::value, void>::type
    mymethod();

    template<typename T>
    typename std::enable_if<std::is_same<T, int>::value, void>::type
    mymethod();
};

template<typename T>
typename std::enable_if<!(std::is_same<T, float>::value || std::is_same<T, int>::value), void>::type
myclass::mymethod() {
    std::cout << "foo bar" << std::endl;
}

template<typename T>
typename std::enable_if<std::is_same<T, float>::value, void>::type
myclass::mymethod() {
    std::cout << "hello" << std::endl;
}

template<typename T>
typename std::enable_if<std::is_same<T, int>::value, void>::type
myclass::mymethod() {
    std::cout << "world" << std::endl;
}
#endif // ENABLE_IF_H
