#ifndef MAT2D_H
#define MAT2D_H

#include <memory>

template<typename T>
class Mat2D {
public:
    Mat2D();
    Mat2D(size_t nrow, size_t ncol);

private:
    std::unique_ptr<T> m_buf;
};

#endif // MAT2D_H
