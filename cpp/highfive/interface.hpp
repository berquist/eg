#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_

#include <highfive/H5File.hpp>
#include "span.hpp"
#include "get_dims.hpp"

using namespace HighFive;

class Interface {
public:
    Interface(const std::string &filename)
        : m_filename(filename)
        , m_file(File(filename, File::ReadWrite | File::Create)) {

    }

    template <typename T>
    void read(const std::string &path, T &value) const {
        DataSet dset = m_file.getDataSet(path);
        dset.read(value);
    }

    template <typename T>
    void write(const std::string &path, const T &value) {
        if (!m_file.exist(path)) {
            // TODO check if a group
            DataSet dset = m_file.createDataSet(path, value);
        } else {
            DataSet dset = m_file.getDataSet(path);
            const DataSpace dspace = dset.getSpace();
            const std::vector<size_t> dims = dspace.getDimensions();
            const std::vector<size_t> dims_max = dspace.getMaxDimensions();
            if (get_dims<T>(value) != dims) {
                throw std::runtime_error("dims don't match");
            } else {
                dset.write(value);
            }
        }
    }

    /**
     *
     * The dimensions of the passed value are assumed
     */
    template <typename T>
    void write(const std::string &path, const T &value, const std::vector<Span> &window);

    std::vector<std::string> get_paths() const {
        std::vector<std::string> paths;
        get_paths(m_file.getPath(), paths);
        return paths;
    }

private:
    const std::string &m_filename;
    File m_file;

    /** DFS over all groups and datasets
     **/
    void get_paths(const std::string &starting_path, std::vector<std::string> &visited_paths) const {
        visited_paths.push_back(starting_path);
        const ObjectType starting_type = m_file.getObjectType(starting_path);
        if (starting_type == ObjectType::Group) {
            const Group level_group = m_file.getGroup(starting_path);
            const std::vector<std::string> level_paths = level_group.listObjectNames();
            for (size_t i = 0; i < level_paths.size(); i++) {
                std::string new_path;
                if (starting_path != m_file.getPath()) {
                    new_path = starting_path + "/" + level_paths[i];
                } else {
                    new_path = m_file.getPath() + level_paths[i];
                }
                get_paths(new_path, visited_paths);
            }
        }
    }
    
};

#endif // INTERFACE_HPP_
