#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_

#include "type_name.hpp"
#include "tgf.hpp"
#include <type_traits>
#include <utility>
#include "common.hpp"
#include <highfive/H5File.hpp>
#include "span.hpp"
#include "get_dims.hpp"

// FIXME how to have these not infect everything that includes this file?
#include "get_dims_arma.hpp"
// #include "get_dims_aview.hpp"

using namespace HighFive;

typedef std::vector<size_t> indices;
typedef std::pair<indices, indices> pair_indices;

inline pair_indices spans_to_offsets_and_counts(const std::vector<Span> &spans) {
    indices offsets;
    indices counts;
    for (const Span &span : spans) {
        offsets.push_back(span.start);
        // stop is inclusive
        counts.push_back(span.stop - span.start + 1);
    }
    return std::make_pair(offsets, counts);
}

class Interface {
public:
    Interface(const std::string &filename)
        : m_filename(filename)
        , m_file(File(filename, File::ReadWrite | File::Create))
        , m_name_group_types(".types")
        , m_group_types(create_or_get_group(m_name_group_types))
        { }

    /**
     * Read the windowed selection of the underlying store at the given path
     * into the given value.
     */
    template <typename T>
    void read(const std::string &path, T &value, const std::vector<Span> &window = {}) const {
        // TODO allow HighFive exception?
        DataSet dset = m_file.getDataSet(path);
        if (window.empty()) {
            dset.read(value);
        } else {
            const pair_indices offsets_and_counts = spans_to_offsets_and_counts(window);
            const indices offset = offsets_and_counts.first;
            const indices count = offsets_and_counts.second;
            dset.select(offset, count).read(value);
        }
    }

    /**
     * Write the given value to the windowed selection of the given path at
     * the underlying store.
     *
     * If a window isn't given, then the whole extent of the dataset will be
     * written to.
     *
     * If it doesn't make sense for the given value to have a window/selection
     * applied, then an exception is thrown.  It only applies to things like
     * std::vector, Armadillo objects, libaview array_views/tensors, etc.
     *
     * If the path doesn't already exist, then the amount of space created in
     * the underlying store is equal to the size of the given window.  (If
     * there were separate add/update methods, then you couldn't add something
     * with a window, that wouldn't make any sense.)
     *
     * If the path already exists, the dimensions of the passed value are
     * assumed to fit within the maximum dimensions of the underlying
     * dataspace.
     */
    template <typename T>
    void write(
        const std::string &path,
        const T &value,
        const std::vector<Span> &window,
        std::false_type) {

        if (!m_file.exist(path)) {
            if (!window.empty()) {
                throw std::runtime_error("it doesn't make sense to specify writing a subset to a nonexistent entry");
            }
            // TODO check if a group
            const DataSet dset = m_file.createDataSet(path, value);
        } else {
            // TODO check if a group
            DataSet dset = m_file.getDataSet(path);
            const DataSpace dspace = dset.getSpace();
            const std::vector<size_t> dims = dspace.getDimensions();
            const std::vector<size_t> dims_max = dspace.getMaxDimensions();
            const std::vector<size_t> dims_value = get_dims(value);
            if (dims_value != dims) {
                std::cout << " dims_value: " << dims_value << std::endl;
                std::cout << " dims: " << dims << std::endl;
                throw std::runtime_error("dims don't match");
            } else {
                if (window.empty()) {
                    dset.write(value);
                } else {
                    const pair_indices offsets_and_counts = spans_to_offsets_and_counts(window);
                    const indices offsets = offsets_and_counts.first;
                    const indices counts = offsets_and_counts.second;
                    dset.select(offsets, counts).write(value);
                }
            }
        }
    }

    template <typename T>
    void write(
        const std::string &path,
        const T &value,
        const std::vector<Span> &window,
        std::true_type) {

        if (!window.empty()) {
            throw std::runtime_error("it doesn't make sense to specify a window for an enum");
        }

        if (!m_file.exist(path)) {
            // TODO check if a group
            //
            // Register/commit the type if it doesn't already
            // exist and use that.
            const std::string enum_type_name = type_name<T>();
            const std::function<EnumType<T>()> highfive_tgf = get_highfive_type_generating_function_enum<T>(enum_type_name);
            const EnumType<T> dtype = highfive_tgf();
            if (!m_file.exist(enum_type_name)) {
                dtype.commit(m_file, enum_type_name);
            }
            // FIXME
            DataSet dset = m_file.createDataSet(path, DataSpace(1), dtype);
            dset.write(value);
        } else {
            // TODO check if a group
            // TODO this can be simplified for enums
            DataSet dset = m_file.getDataSet(path);
            const DataSpace dspace = dset.getSpace();
            const std::vector<size_t> dims = dspace.getDimensions();
            const std::vector<size_t> dims_max = dspace.getMaxDimensions();
            const std::vector<size_t> dims_value = get_dims(value);
            if (dims_value != dims) {
                std::cout << " dims_value: " << dims_value << std::endl;
                std::cout << " dims: " << dims << std::endl;
                throw std::runtime_error("dims don't match");
            } else {
                dset.write(value);
            }
        }
    }

    template <typename T>
    void write(
        const std::string &path,
        const T &value,
        const std::vector<Span> &window = {}) {
        return write(path, value, window, std::is_enum<T>{});
    }

    std::vector<std::string> get_paths() const noexcept {
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

    /** \brief Create a group if it doesn't already exist.
     **/
    Group create_or_get_group(const std::string &group_name) {
        if (!m_file.exist(group_name)) {
            return m_file.createGroup(group_name);
        } else {
            return m_file.getGroup(group_name);
        }
    }

    const std::string m_name_group_types;
    Group m_group_types;
};

#endif // INTERFACE_HPP_
