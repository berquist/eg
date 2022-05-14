#include <iostream>
#include <memory>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &v) {
    os << "[ ";
    for (size_t i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }
    os << "]";
    return os;
}

struct A {
    A(
        const std::string &name,
        std::vector<std::shared_ptr<A>> &stack,
        std::vector<std::weak_ptr<A>> &stack_w,
        std::vector<A*> &stack_r)
        : m_name(name)
        , m_stack(stack)
        , m_stack_w(stack_w)
        , m_stack_r(stack_r) {

        std::cout<< "[A] " << m_name << std::endl;
        m_stack_r.push_back(this);
    }

    virtual ~A() {
        std::cout<< "[~A] " << m_name << std::endl;
        m_stack_r.pop_back();
    }

    const std::string m_name;
    std::vector<std::shared_ptr<A>> &m_stack;
    std::vector<std::weak_ptr<A>> &m_stack_w;
    std::vector<A*> &m_stack_r;
};

struct Deleters {
    void operator()(A * x) const {
        std::cout << "[$A] " << x->m_name << std::endl;
        delete x;
    }
};

int main() {
    std::cout << "=== main ===" << std::endl;

    std::vector<std::shared_ptr<A>> stack;
    std::vector<std::weak_ptr<A>> stack_w;
    std::vector<A*> stack_r;

    Deleters d;

    auto foo = std::shared_ptr<A>(new A("foo", stack, stack_w, stack_r), d);
    std::cout << "foo: " << foo.get() << std::endl;
    std::cout << stack_r << std::endl;
    {
        {
            auto bar = std::shared_ptr<A>(new A("bar", stack, stack_w, stack_r), d);
            std::cout << "bar: " << bar.get() << std::endl;
            std::cout << stack_r << std::endl;
        }
        auto baz = std::shared_ptr<A>(new A("baz", stack, stack_w, stack_r), d);
        std::cout << "baz: " << baz.get() << std::endl;
        std::cout << stack_r << std::endl;
    }
    std::cout << stack_r << std::endl;

    std::cout << "=== ~main ===" << std::endl;
    return 0;
}
