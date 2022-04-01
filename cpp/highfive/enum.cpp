#include "interface.hpp"
#include <highfive/H5DataSpace.hpp>
#include <highfive/H5DataType.hpp>

using namespace HighFive;

enum perturbation_type {
    electric,
    magnetic,
    geometric
};

enum class mecp_algorithm {
    branching_plane,
    direct,
    penalty_function
};

std::ostream& operator<<(std::ostream &os, const perturbation_type &pt) {
    switch (pt) {
    case perturbation_type::electric:
        os << "perturbation_type::electric";
        break;
    case perturbation_type::magnetic:
        os << "perturbation_type::magnetic";
        break;
    case perturbation_type::geometric:
        os << "perturbation_type::geometric";
        break;
    }
    return os;
}

std::ostream& operator<<(std::ostream &os, const mecp_algorithm &alg) {
    switch (alg) {
    case mecp_algorithm::branching_plane:
        os << "mecp_algorithm::branching_plane";
        break;
    case mecp_algorithm::direct:
        os << "mecp_algorithm::direct";
        break;
    case mecp_algorithm::penalty_function:
        os << "mecp_algorithm::penalty_function";
        break;
    }
    return os;
}

enum Position {
    FIRST = 1,
    SECOND = 2,
    THIRD = 3,
    LAST = -1,
};

enum class Direction : signed char {
    FORWARD = 1,
    BACKWARD = -1,
    LEFT = -2,
    RIGHT = 2,
};

EnumType<Position> create_enum_position() {
    return {{"FIRST", Position::FIRST},
            {"SECOND", Position::SECOND},
            {"THIRD", Position::THIRD},
            {"LAST", Position::LAST}};
}
HIGHFIVE_REGISTER_TYPE(Position, create_enum_position)

EnumType<Direction> create_enum_direction() {
    return {{"FORWARD", Direction::FORWARD},
            {"BACKWARD", Direction::BACKWARD},
            {"LEFT", Direction::LEFT},
            {"RIGHT", Direction::RIGHT}};
}
HIGHFIVE_REGISTER_TYPE(Direction, create_enum_direction)

// example stolen from HighFive unit tests
#if 0
TEST_CASE("HighFiveEnum") {
    const std::string FILE_NAME("enum_test.h5");
    const std::string DATASET_NAME1("/a");
    const std::string DATASET_NAME2("/b");

    File file(FILE_NAME, File::ReadWrite | File::Create | File::Truncate);

    {  // Unscoped enum
        auto e1 = create_enum_position();
        e1.commit(file, "Position");

        auto dataset = file.createDataSet(DATASET_NAME1, DataSpace(1), e1);
        dataset.write(Position::FIRST);

        file.flush();

        Position result;
        dataset.select(ElementSet({0})).read(result);

        CHECK(result == Position::FIRST);
    }

    {  // Scoped enum
        auto e1 = create_enum_direction();
        e1.commit(file, "Direction");

        auto dataset = file.createDataSet(DATASET_NAME2, DataSpace(5), e1);
        std::vector<Direction> robot_moves({Direction::BACKWARD, Direction::FORWARD,
                                            Direction::FORWARD, Direction::LEFT,
                                            Direction::LEFT});
        dataset.write(robot_moves);

        file.flush();

        std::vector<Direction> result;
        dataset.read(result);

        CHECK(result[0] == Direction::BACKWARD);
        CHECK(result[1] == Direction::FORWARD);
        CHECK(result[2] == Direction::FORWARD);
        CHECK(result[3] == Direction::LEFT);
        CHECK(result[4] == Direction::LEFT);
    }
}
#endif

EnumType<perturbation_type> create_enum_perturbation_type() {
    return {{"electric", perturbation_type::electric},
            {"magnetic", perturbation_type::magnetic},
            {"geometric", perturbation_type::geometric}};
}
HIGHFIVE_REGISTER_TYPE(perturbation_type, create_enum_perturbation_type);

EnumType<mecp_algorithm> create_enum_mecp_algorithm() {
    return {{"branching_plane", mecp_algorithm::branching_plane},
            {"direct", mecp_algorithm::direct},
            {"penalty_function", mecp_algorithm::penalty_function}};
}
HIGHFIVE_REGISTER_TYPE(mecp_algorithm, create_enum_mecp_algorithm);

int main() {
    const std::string filename("enum.h5");
    File file(filename, File::ReadWrite | File::Create | File::Truncate);

    Interface iface(filename);

    constexpr auto e1 = perturbation_type::magnetic;
    constexpr auto e2 = mecp_algorithm::penalty_function;

    std::cout << e1 << std::endl;
    std::cout << e2 << std::endl;

    std::cout << unsigned(e1) << std::endl;
    std::cout << unsigned(e2) << std::endl;

    std::stringstream ss;
    ss.str(std::string());
    ss << e1;
    // iface.write("/e1", ss.str());
    ss.str(std::string());
    ss << e2;
    // iface.write("/e2", ss.str());

    // iface.write("/dir", Direction::LEFT);
    // iface.write("/pos", Position::THIRD);

    auto e1t = create_enum_perturbation_type();
    auto e2t = create_enum_mecp_algorithm();

    e1t.commit(file, "perturbation_type");
    e2t.commit(file, "mecp_algorithm");

    // iface.write("/e1t", e1);
    // iface.write("/e2t", e2);

    auto dset1 = file.createDataSet("e1t", DataSpace(1), e1t);
    auto dset2 = file.createDataSet("e2t", DataSpace(1), e2t);
    dset1.write(e1);
    dset2.write(e2);

    auto dset1n = file.createDataSet("e1n", e1);
    auto dset2n = file.createDataSet("e2n", e2);
    // auto dset1tn = file.createDataSet<EnumType<perturbation_type>>("e1tn", e1);
    // auto dset2tn = file.createDataSet<EnumType<mecp_algorithm>>("e2tn", e2);

    return 0;
}
