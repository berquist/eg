#include <algorithm>
#include <iostream>
#include <typeinfo>
#include <utility>
#include <vector>
#include "type_name.hpp"

template<class T>
struct inner_class_of { using outer_class = T; };

template<class T>
inner_class_of<T> get_outer_helper(inner_class_of<T>const&);

template<class T>
using outer_class_of_t = typename decltype(get_outer_helper(std::declval<T>()))::outer_class;

struct schema_base {} schema_base_;
struct iterable {};
struct is_iter {};
struct can_add_sp {};

// This kind of entry keeps track of the dtype it contains using a template parameter.
template<typename TD>
struct entry {
    const char *key;
    const char *title;
    const entry<void> *parent;
};

// This kind of entry also keeps track of the schema struct it's contained in.
// However, we can't keep a pointer to the parent entry (_), since its TC is
// not fixed.
template<typename TD, typename TC>
struct entry2 {
    const char *key;
    const char *title;
};

template<typename TD>
std::ostream& operator<<(std::ostream &os, const entry<TD> &e) {
    os << "{ " << e.key << ", "<< e.title << " [" << type_name<TD>() << "] }";
    return os;
}

template<typename TD, typename TC>
std::ostream& operator<<(std::ostream &os, const entry2<TD, TC> &e) {
    os << "{ " << e.key << ", "<< e.title << " [" << type_name<TD>() << ", " << type_name<TC>() << "] }";
    return os;
}

enum class mecp_algorithm {
    branching_plane,
    direct,
    penalty_function
};
struct mecp_state {
    bool spin;
    unsigned irrep;
    unsigned state_within_irrep;
};

struct energy_functions: inner_class_of<schema_base> {
    static const entry<void> _;
    struct scf: iterable, inner_class_of<energy_functions> {
        static const entry<void> _;
        struct iter: is_iter, inner_class_of<scf> {
            static const entry<void> _;
            static const entry<double> mo_coefficients;
            static const entry<double> energy;
        };
    };
};

struct job: can_add_sp, is_iter, inner_class_of<schema_base> {
    static const entry<void> _;
    static const entry<char*> jobtype;

    struct mecp: iterable, inner_class_of<job> {
        static const entry<void> _;
        static const entry<mecp_algorithm> algorithm;
        static const entry<mecp_state> state_of_interest_1;
        static const entry<mecp_state> state_of_interest_2;
        struct step: can_add_sp, is_iter, inner_class_of<mecp> {
            static const entry<void> _;
            static const entry<mecp_state> state1;
            static const entry<mecp_state> state2;
            static const entry<double> ediff;
        };
    };
};

// const entry<void> energy_functions::_ = {"energy_functions", "Energy functions", 0};
// const entry<void> energy_functions::scf::_ = {"scf", "SCF", &energy_functions::_};
const entry<void> energy_functions::scf::_ = {"scf", "SCF", 0};
const entry<void> energy_functions::scf::iter::_ = {"iter", "SCF iteration", &energy_functions::scf::_};
const entry<double> energy_functions::scf::iter::mo_coefficients = {"mo_coefficients", "MO coefficients", &energy_functions::scf::iter::_};
const entry<double> energy_functions::scf::iter::energy = {"energy", "Energy", &energy_functions::scf::iter::_};
const entry<void> job::_ = {"job", "Job", 0};
const entry<char*> job::jobtype = {"jobtype", "Job type", &job::_};
const entry<void> job::mecp::_ = {"mecp", "Minimum energy crossing point optimization", &job::_};
const entry<mecp_algorithm> job::mecp::algorithm = {"algorithm", "MECP algorithm", &job::mecp::_};
const entry<mecp_state> job::mecp::state_of_interest_1 = {"state_of_interest_1", "MECP state 1", &job::mecp::_};
const entry<mecp_state> job::mecp::state_of_interest_2 = {"state_of_interest_2", "MECP state 2", &job::mecp::_};
const entry<void> job::mecp::step::_ = {"step", "MECP iteration", &job::mecp::_};
const entry<mecp_state> job::mecp::step::state1 = {"state1", "MECP current state 1", &job::mecp::step::_};
const entry<mecp_state> job::mecp::step::state2 = {"state2", "MECP current state 2", &job::mecp::step::_};
const entry<double> job::mecp::step::ediff = {"ediff", "State energy difference", &job::mecp::step::_};

struct energy_functions2: inner_class_of<schema_base> {
    static const entry2<void, energy_functions2> _;
    struct scf2: iterable, inner_class_of<energy_functions2> {
        static const entry2<void, scf2> _;
        struct iter2: is_iter, inner_class_of<scf2> {
            static const entry2<void, iter2> _;
            static const entry2<double, iter2> mo_coefficients;
            static const entry2<double, iter2> energy;
        };
    };
};

struct job2: can_add_sp, is_iter, inner_class_of<schema_base> {
    static const entry2<void, job2> _;
    static const entry2<char*, job2> jobtype;

    struct mecp2: iterable, inner_class_of<job2> {
        static const entry2<void, mecp2> _;
        static const entry2<mecp_algorithm, mecp2> algorithm;
        static const entry2<mecp_state, mecp2> state_of_interest_1;
        static const entry2<mecp_state, mecp2> state_of_interest_2;
        struct step2: can_add_sp, is_iter, inner_class_of<mecp2> {
            static const entry2<void, step2> _;
            static const entry2<mecp_state, step2> state1;
            static const entry2<mecp_state, step2> state2;
            static const entry2<double, step2> ediff;
        };
    };
};

// const entry2<void, energy_functions2> energy_functions2::_ = {"energy_functions", "Energy functions"};
const entry2<void, energy_functions2::scf2> energy_functions2::scf2::_ = {"scf", "SCF"};
const entry2<void, energy_functions2::scf2::iter2> energy_functions2::scf2::iter2::_ = {"iter", "SCF iteration"};
const entry2<double, energy_functions2::scf2::iter2> energy_functions2::scf2::iter2::mo_coefficients = {"mo_coefficients", "MO coefficients"};
const entry2<double, energy_functions2::scf2::iter2> energy_functions2::scf2::iter2::energy = {"energy", "Energy"};
const entry2<void, job2> job2::_ = {"job", "Job"};
const entry2<char*, job2> job2::jobtype = {"jobtype", "Job type"};
const entry2<void, job2::mecp2> job2::mecp2::_ = {"mecp", "Minimum energy crossing point optimization"};
const entry2<mecp_algorithm, job2::mecp2> job2::mecp2::algorithm = {"algorithm", "MECP algorithm"};
const entry2<mecp_state, job2::mecp2> job2::mecp2::state_of_interest_1 = {"state_of_interest_1", "MECP state 1"};
const entry2<mecp_state, job2::mecp2> job2::mecp2::state_of_interest_2 = {"state_of_interest_2", "MECP state 2"};
const entry2<void, job2::mecp2::step2> job2::mecp2::step2::_ = {"step", "MECP iteration"};
const entry2<mecp_state, job2::mecp2::step2> job2::mecp2::step2::state1 = {"state1", "MECP current state 1"};
const entry2<mecp_state, job2::mecp2::step2> job2::mecp2::step2::state2 = {"state2", "MECP current state 2"};
const entry2<double, job2::mecp2::step2> job2::mecp2::step2::ediff = {"ediff", "State energy difference"};

constexpr static auto counter_placeholder = "???counter???";

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &v) {
    os << "[ ";
    for (size_t i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }
    os << "]";
    return os;
}

std::vector<std::string> split(const std::string &s, const std::string &delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

template<typename TD>
void traverse(const entry<TD> &e) {
    std::vector<std::string> components{std::string(e.key)};
    const entry<void> *eee = e.parent;
    while(eee) {
        components.push_back(std::string(eee->key));
        eee = eee->parent;
    }
    std::reverse(components.begin(), components.end());
    std::cout << components << std::endl;
}

// template<typename TD>
// void traverse(const entry2<TD, schema_base> &e) {
    
// }

template<typename T>
void traverse_schema();

template<> void traverse_schema<schema_base>() {
    std::cout << "base" << std::endl;
}

template<typename T>
void traverse_schema() {
    std::vector<std::string> components = split(type_name<T>(), "::");
    std::cout << components[components.size() - 1] << std::endl;
    traverse_schema<outer_class_of_t<T>>();
}

template<typename TD, typename TC>
void traverse(const entry2<TD, TC> &e) {
    // TODO two possible options:
    // 1. type_name provides the fully-qualified (?) name, just split on "::" to get the pieces
    // 2. use type_name, split on "::", then take the last component,
    //    then use TC in call to traverse_schema that recursively uses outer_class_of_t
    // go with option 2? easy to check if something is `is_iter` or similar
    std::cout << e.key << std::endl;
    traverse_schema<TC>();
}

int main() {
    // const auto e = job::mecp::step::state2;
    const auto e = energy_functions::scf::iter::energy;
    std::cout << e << std::endl;
    traverse(e);
    // const auto e2 = job2::mecp2::step2::state2;
    const auto e2 = energy_functions2::scf2::iter2::energy;
    std::cout << e2 << std::endl;
    traverse(e2);
    return 0;
}
