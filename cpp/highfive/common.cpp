#include "common.hpp"

using namespace HighFive;

std::ostream& operator<<(std::ostream &os, const ObjectType &ot) {
    switch (ot) {
    case ObjectType::File:
        os << "ObjectType::File";
        break;
    case ObjectType::Group:
        os << "ObjectType::Group";
        break;
    case ObjectType::UserDataType:
        os << "ObjectType::UserDataType";
        break;
    case ObjectType::DataSpace:
        os << "ObjectType::DataSpace";
        break;
    case ObjectType::Dataset:
        os << "ObjectType::Dataset";
        break;
    case ObjectType::Attribute:
        os << "ObjectType::Attribute";
        break;
    case ObjectType::Other:
        os << "ObjectType::Other";
        break;
    default:
        throw std::invalid_argument("invalid argument to operator<< for HighFive::ObjectType");
    }
    return os;
}
