#include <fstream>

#include <cereal/archives/binary.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>

struct MyClass
{
    int x, y, z;

    // This method lets cereal know which data members to serialize
    template<class Archive>
    void serialize(Archive &archive) {
        archive( x, y, z ); // serialize things by passing them to the archive
    }
};

int main() {
    MyClass m1_ref { 23, 11, 42 };
    MyClass m2_ref { 33, 21, 92 };
    MyClass m3_ref { 53, 31, 182 };

    std::ofstream ss_binary("myclass.bin"); // any stream can be used
    std::ofstream ss_port_binary("myclass_port.bin");
    std::ofstream ss_xml("myclass.xml");
    std::ofstream ss_json("myclass.json");
    {
        cereal::BinaryOutputArchive oarchive_binary(ss_binary); // Create an output archive
        cereal::PortableBinaryOutputArchive oarchive_port_binary(ss_port_binary);
        cereal::XMLOutputArchive oarchive_xml(ss_xml);
        cereal::JSONOutputArchive oarchive_json(ss_json);

        oarchive_binary(m1_ref, m2_ref, m3_ref); // Write the data to the archive
        oarchive_port_binary(m1_ref, m2_ref, m3_ref); // Write the data to the archive
        oarchive_xml(m1_ref, m2_ref, m3_ref); // Write the data to the archive
        oarchive_json(m1_ref, m2_ref, m3_ref); // Write the data to the archive

    } // archive goes out of scope, ensuring all contents are flushed

    // {
    //     cereal::BinaryInputArchive iarchive_binary(ss_binary); // Create an input archive

    //     MyClass m1, m2, m3;
    //     iarchive(m1, m2, m3); // Read the data from the archive

    // }
    return 0;
}
