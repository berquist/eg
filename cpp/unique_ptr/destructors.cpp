#include <iostream>
#include <memory>

struct A {
    A(const std::string &name) : m_name(name) {
        std::cout<< "[A] " << m_name << std::endl;
    }
    ~A() {
        std::cout<< "[~A] " << m_name << std::endl;
    }
    std::string m_name;
};

struct B {
    B(const std::string &name) : m_name(name) {
        std::cout<< "[B] " << m_name << std::endl;
    }
    ~B() {
        std::cout<< "[~B] " << m_name << std::endl;
    }
    std::string m_name;
} B_inst("global");

struct Deleters {
    void operator()(A * x) const {
        std::cout << "deleting [A] " << x->m_name << std::endl;
        delete x;
    }

    void operator()(B * x) const {
        std::cout << "deleting [B] " << x->m_name << std::endl;
        delete x;
    }
};

int main() {
    A Afirst("1");
    A Asecond("2");
    A Athird("3");
    B Bfirst("1");
    B Bsecond("2");
    {
        A Afourth("4");
        B Bfourth("4");
    }
    B Bthird("3");
    // no deleter for make_shared
    // auto Bfifth = std::make_shared<B>("5");
    std::shared_ptr<B> Bfifth(new B("5"), Deleters());
    std::unique_ptr<A, Deleters> Afifth(new A("5"));
    std::cout << "reached end of main" << std::endl;
    return 0;
}
