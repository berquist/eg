#ifndef H5CPP_ARMA_HPP_
#define H5CPP_ARMA_HPP_

#include <armadillo>
#include <h5cpp/hdf5.hpp>

// implementation ordering:
//  - Col, Row, Mat, Cube
//  - double, uword, sword

namespace hdf5 {
    namespace dataspace {
        template<typename T> class TypeTrait<arma::Col<T> > {
        public:
            using DataspaceType = Simple;
            static DataspaceType create(const arma::Col<T> &v) {
                return Simple({v.n_rows, v.n_cols});
            }
            static void *ptr(arma::Col<T> &v) {
                return reinterpret_cast<void*>(v.memptr());
            }
            static const void *cptr(const arma::Col<T> &v) {
                return reinterpret_cast<const void*>(v.memptr());
            }
        };
        template<typename T> class TypeTrait<arma::Row<T> > {
        public:
            using DataspaceType = Simple;
            static DataspaceType create(const arma::Row<T> &v) {
                return Simple({v.n_rows, v.n_cols});
            }
            static void *ptr(arma::Row<T> &v) {
                return reinterpret_cast<void*>(v.memptr());
            }
            static const void *cptr(const arma::Row<T> &v) {
                return reinterpret_cast<const void*>(v.memptr());
            }
        };
        template<typename T> class TypeTrait<arma::Mat<T> > {
        public:
            using DataspaceType = Simple;
            static DataspaceType create(const arma::Mat<T> &v) {
                return Simple({v.n_rows, v.n_cols});
            }
            static void *ptr(arma::Mat<T> &v) {
                return reinterpret_cast<void*>(v.memptr());
            }
            static const void *cptr(const arma::Mat<T> &v) {
                return reinterpret_cast<const void*>(v.memptr());
            }
        };
        template<typename T> class TypeTrait<arma::Cube<T> > {
        public:
            using DataspaceType = Simple;
            static DataspaceType create(const arma::Cube<T> &v) {
                return Simple({v.n_rows, v.n_cols, v.n_slices});
            }
            static void *ptr(arma::Cube<T> &v) {
                return reinterpret_cast<void*>(v.memptr());
            }
            static const void *cptr(const arma::Cube<T> &v) {
                return reinterpret_cast<const void*>(v.memptr());
            }
        };
    }
    namespace datatype {

        template<> class TypeTrait<arma::Col<double> > {
        public:
            using Type = arma::Col<double>;
            using TypeClass = Float;
            static TypeClass create(const Type & = Type()) {
                return TypeTrait<double>::create();
            }
        };
        template<> class TypeTrait<arma::Row<double> > {
        public:
            using Type = arma::Row<double>;
            using TypeClass = Float;
            static TypeClass create(const Type & = Type()) {
                return TypeTrait<double>::create();
            }
        };
        template<> class TypeTrait<arma::Mat<double> > {
        public:
            using Type = arma::Mat<double>;
            using TypeClass = Float;
            static TypeClass create(const Type & = Type()) {
                return TypeTrait<double>::create();
            }
        };
        template<> class TypeTrait<arma::Cube<double> > {
        public:
            using Type = arma::Cube<double>;
            using TypeClass = Float;
            static TypeClass create(const Type & = Type()) {
                return TypeTrait<double>::create();
            }
        };

        template<> class TypeTrait<arma::Col<arma::uword> > {
        public:
            using Type = arma::Col<arma::uword>;
            using TypeClass = Integer;
            static TypeClass create(const Type & = Type()) {
                return TypeTrait<arma::uword>::create();
            }
        };
        template<> class TypeTrait<arma::Row<arma::uword> > {
        public:
            using Type = arma::Row<arma::uword>;
            using TypeClass = Integer;
            static TypeClass create(const Type & = Type()) {
                return TypeTrait<arma::uword>::create();
            }
        };
        template<> class TypeTrait<arma::Mat<arma::uword> > {
        public:
            using Type = arma::Mat<arma::uword>;
            using TypeClass = Integer;
            static TypeClass create(const Type & = Type()) {
                return TypeTrait<arma::uword>::create();
            }
        };
        template<> class TypeTrait<arma::Cube<arma::uword> > {
        public:
            using Type = arma::Cube<arma::uword>;
            using TypeClass = Integer;
            static TypeClass create(const Type & = Type()) {
                return TypeTrait<arma::uword>::create();
            }
        };

        template<> class TypeTrait<arma::Col<arma::sword> > {
        public:
            using Type = arma::Col<arma::sword>;
            using TypeClass = Integer;
            static TypeClass create(const Type & = Type()) {
                return TypeTrait<arma::sword>::create();
            }
        };
        template<> class TypeTrait<arma::Row<arma::sword> > {
        public:
            using Type = arma::Row<arma::sword>;
            using TypeClass = Integer;
            static TypeClass create(const Type & = Type()) {
                return TypeTrait<arma::sword>::create();
            }
        };
        template<> class TypeTrait<arma::Mat<arma::sword> > {
        public:
            using Type = arma::Mat<arma::sword>;
            using TypeClass = Integer;
            static TypeClass create(const Type & = Type()) {
                return TypeTrait<arma::sword>::create();
            }
        };
        template<> class TypeTrait<arma::Cube<arma::sword> > {
        public:
            using Type = arma::Cube<arma::sword>;
            using TypeClass = Integer;
            static TypeClass create(const Type & = Type()) {
                return TypeTrait<arma::sword>::create();
            }
        };
    }
}

#endif // H5CPP_ARMA_HPP_
