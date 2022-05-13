#include <iostream>

class A {
public:
    A(const std::string &s)
        : m_s(s) {

        std::cout << "[A] " << m_s << std::endl;
    }
    ~A() {
        std::cout << "[~A] " << m_s << std::endl;
    }

protected:
    const std::string m_s;
};

class B : public A {
public:
    B(const std::string &s)
        : A(s) {

        std::cout << "[B] " << m_s << std::endl;
    }
    ~B() {
        std::cout << "[~B] " << m_s << std::endl;
    }
};

class C : public B {
public:
    C(const std::string &s)
        : B(s) {

        std::cout << "[C] " << m_s << std::endl;
    }
    ~C() {
        std::cout << "[~C] " << m_s << std::endl;
    }
};

class D {
public:
    D(const std::string &s)
        : m_s(s) {

        std::cout << "[D] " << m_s << std::endl;
    }
    virtual ~D() {
        std::cout << "[~D] " << m_s << std::endl;
    }

protected:
    const std::string m_s;
};

class E : public D {
public:
    E(const std::string &s)
        : D(s) {

        std::cout << "[E] " << m_s << std::endl;
    }
    virtual ~E() {
        std::cout << "[~E] " << m_s << std::endl;
    }
};

class F : public E {
public:
    F(const std::string &s)
        : E(s) {

        std::cout << "[F] " << m_s << std::endl;
    }
    ~F() {
        std::cout << "[~F] " << m_s << std::endl;
    }
};


int main() {
    B b1("b1");
    C c1("c1");
    A * c2 = new C("c2");
    delete c2;
    D * d1 = new D("d1");
    delete d1;
    D * e1 = new E("e1");
    delete e1;
    D * f1 = new F("f1");
    delete f1;
    return 0;
}
