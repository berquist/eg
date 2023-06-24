#include "common.hpp"
#include "interface.hpp"
#include <H5Ipublic.h>
#include <H5Opublic.h>
#include <H5Tpublic.h>
#include <highfive/H5DataSpace.hpp>
#include <highfive/H5DataType.hpp>

using namespace HighFive;

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

// TODO why can't these live in common.cpp?
HIGHFIVE_REGISTER_TYPE(perturbation_type, create_enum_perturbation_type)
HIGHFIVE_REGISTER_TYPE(mecp_algorithm, create_enum_mecp_algorithm)

template<typename T>
bool dtype_matches(const T &type_container, const std::string &candidate_type_name, const DataType &other_dtype) {
    const auto candidate_type_id = H5Oopen(type_container.getId(), candidate_type_name.c_str(), H5P_DEFAULT);
    if (candidate_type_id < 0) {
        throw std::runtime_error("failed to open type object");
    }
    const bool is_equal = H5Tequal(candidate_type_id, other_dtype.getId()) > 0;
    const auto close_err = H5Oclose(candidate_type_id);
    if (close_err < 0) {
        throw std::runtime_error("failed to close type object");
    }
    return is_equal;
}

std::string h5i_get_name(hid_t id) {
    const auto name_size = H5Iget_name(id, NULL, 0);
    char * name = (char*)malloc(name_size + 1);
    H5Iget_name(id, name, name_size + 1);
    const std::string name_str(name);
    free(name);
    return name_str;
}

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

    std::cout << type_name<decltype(e1)>() << std::endl;
    std::cout << type_name<decltype(e2)>() << std::endl;

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

    iface.write("e1_2", e1);
    iface.write("e2_2", e2);

    const auto dset_global = file.getDataSet("e1t");
    const auto dtype_global = dset_global.getDataType();
    const auto dset_local = file.getDataSet("e1n");
    const auto dtype_local = dset_local.getDataType();
    const auto dtype_other = file.getDataSet("e2t").getDataType();
    std::cout << "dtype match? (same) = " << (dtype_global == dtype_local) << std::endl;
    std::cout << "dtype match? (different) = " << (dtype_global == dtype_other) << std::endl;
    // These are not necessarily the same, even if the DataTypes match.
    // std::cout << dtype_global.getId() << std::endl;
    // std::cout << dtype_local.getId() << std::endl;
    // std::cout << dtype_other.getId() << std::endl;

    // See if the type of the enum maches a type that's already been
    // committed.

    const std::string candidate_type_name("perturbation_type");
    const std::string different_type_name("mecp_algorithm");
    const std::string invalid_type_name("hello_world");
    const auto type_container = file;
    if (type_container.exist(candidate_type_name)) {
        const auto type = type_container.getObjectType(candidate_type_name);
        if (type == ObjectType::UserDataType) {
            SilenceHDF5 silencer;
            const auto candidate_type_id = H5Oopen(type_container.getId(), candidate_type_name.c_str(), H5P_DEFAULT);
            std::cout << H5Tequal(candidate_type_id, dtype_local.getId()) << std::endl;
            std::cout << H5Tequal(candidate_type_id, dtype_global.getId()) << std::endl;
            std::cout << H5Tequal(candidate_type_id, dtype_other.getId()) << std::endl;
            const auto close_err = H5Oclose(candidate_type_id);
            const auto invalid_type_id = H5Oopen(type_container.getId(), invalid_type_name.c_str(), H5P_DEFAULT);
            if (invalid_type_id < 0) {
                // TODO handle error
            }
            std::cout << invalid_type_id << std::endl;
        } else {
            //  TODO
        }
    }
    std::cout << "function (local): " << dtype_matches(file, "perturbation_type", dtype_local) << std::endl;
    std::cout << "function (global): " << dtype_matches(file, "perturbation_type", dtype_global) << std::endl;
    std::cout << "function (other): " << dtype_matches(file, "perturbation_type", dtype_other) << std::endl;
    std::cout << "function (function): " << dtype_matches(file, "perturbation_type",  create_enum_perturbation_type()) << std::endl;
    std::cout << "function (create_and_check): " << dtype_matches(file, "perturbation_type", create_and_check_datatype<perturbation_type>()) << std::endl;

    // How to obtain the path to a referred (global) datatype of a dataset?

    // These are just Enum32.
    // std::cout << dtype_global.string() << std::endl;
    // std::cout << dtype_local.string() << std::endl;

    // auto info_global = dtype_global.getInfo();
    H5O_info2_t oinfo_global;
    H5Oget_info3(dtype_global.getId(), &oinfo_global, H5O_INFO_ALL);
    std::cout << oinfo_global.type << std::endl;
#if 0
    // I don't think the token is important for doing the type of linking I need.
    char token_str_buf[128];
    char *token_str_ptr;
    H5Otoken_to_str(dtype_global.getId(), &oinfo_global.token, &token_str_ptr);
    snprintf(token_str_buf, sizeof(token_str_buf), "/#%s\n", token_str_ptr);
    std::string token_str(token_str_buf);
    std::cout << token_str << std::endl;
#endif
    // not a named datatype
    // H5O_info2_t oinfo_local;
    // H5Oget_info3(dtype_local.getId(), &oinfo_local, 0);
    // std::cout << oinfo_local.type << std::endl;
    std::cout << "===" << std::endl;

    std::cout << e1t.getId() << std::endl;
    std::cout << dtype_global.getId() << std::endl;

    std::cout << h5i_get_name(e1t.getId()) << std::endl;
    std::cout << h5i_get_name(dtype_global.getId()) << std::endl;
    // not a named datatype
    // std::cout << h5i_get_name(dtype_local.getId()) << std::endl;

    return 0;
}
