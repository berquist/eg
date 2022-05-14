#include <iostream>
#include <memory>
#include <vector>

struct A {
    A(const std::string &name) : m_name(name) {
        std::cout<< "[A] " << m_name << std::endl;
    }
    virtual ~A() {
        std::cout<< "[~A] " << m_name << std::endl;
    }
    std::string m_name;
};

struct Deleters {
    void operator()(A * x) const {
        std::cout << "[$A] " << x->m_name << std::endl;
        delete x;
    }
};

void do_something_shared(std::shared_ptr<A> p) {
    std::cout << " [shared] name: " << p->m_name << std::endl;;
    std::cout << " [shared] use count: " << p.use_count() << std::endl;;
}

void do_something_weak(std::weak_ptr<A> p) {
    const bool expired = p.expired();
    std::cout << " [weak] expired: " << expired << std::endl;
    std::cout << " [weak] use count: " << p.use_count() << std::endl;
    if (!expired) {
        const auto shared = p.lock();
        std::cout << " [weak] name: " << shared->m_name << std::endl;;
        do_something_shared(shared);
    }
    std::cout << " [weak] use count: " << p.use_count() << std::endl;
}

int main() {
    std::cout << "=== main ===" << std::endl;

    std::vector<std::shared_ptr<A>> stack;
    std::vector<std::weak_ptr<A>> stack_w;

    Deleters d;

    auto foo = std::shared_ptr<A>(new A("foo"), d);
    stack_w.push_back(std::weak_ptr<A>(foo));
    {
        {
            auto bar = std::shared_ptr<A>(new A("bar"), d);
            stack_w.push_back(std::weak_ptr<A>(bar));
            do_something_shared(bar);
            do_something_weak(stack_w.back());
        }
        auto baz = std::shared_ptr<A>(new A("baz"), d);
        stack_w.push_back(std::weak_ptr<A>(baz));
    }

    std::cout << "=== ~main ===" << std::endl;
    return 0;
}
