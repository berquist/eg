#include <algorithm>
#include <cassert>
#include <cmath>
#include <string.h>

template <class T> class FTensor {

  protected:
    T *m_ptr;
    int m_nDim;
    int m_ldim[6];
    size_t m_offset[6];
    int m_ownptr;
    int m_counter;

  public:
    void operator+=(FTensor<T> &a) {
        T *tptr = a.get_ptr();
        size_t nsz = size();
        for (size_t i = 0; i < nsz; ++i) {
            m_ptr[i] += tptr[i];
        }
    }
    void operator*=(T a) {
        for (size_t i = 0, nsz = size(); i < nsz; ++i) {
            m_ptr[i] *= a;
        }
    }

  public:
    void operator=(T a) {
        for (size_t i = 0, nsz = size(); i < nsz; ++i) {
            m_ptr[i] = a;
        }
    }
    void zero() {
        size_t nsz = size();
        memset(m_ptr, 0, sizeof(T) * nsz);
    }
    void operator=(FTensor<T> &a) { shallow_copy(a); }
    void duplicate(FTensor<T> &a) { deep_copy(a); }
    void copy_dim(const FTensor<T> &a) {
        m_nDim = a.m_nDim;
        for (int i = 0; i < m_nDim; i++) {
            m_ldim[i] = a.m_ldim[i];
            m_offset[i] = a.m_offset[i];
        }
    }
    void init_new(const FTensor &a) {
        if (m_ownptr == 1) {
            delete[] m_ptr;
        }
        copy_dim(a);
        int nsz = size();
        m_ptr = new T[nsz];
        m_ownptr = 1;
        memset(m_ptr, 0, nsz * sizeof(T));
    }
    void shallow_copy(const FTensor &a) {
        if (m_ownptr == 1) {
            delete[] m_ptr;
        }
        copy_dim(a);
        m_ptr = a.m_ptr;
        m_ownptr = 0;
    }
    void deep_copy(const FTensor &a) {
        if (m_ownptr == 1) {
            delete[] m_ptr;
        }
        copy_dim(a);
        size_t nsz = size();
        m_ptr = new T[nsz];
        memcpy(m_ptr, a.m_ptr, nsz * sizeof(T));
        m_ownptr = 1;
    }

  private:
    void setOffset() {
        size_t loff = 1;
        for (int i = 0; i < m_nDim; i++) {
            m_offset[i] = loff;
            loff *= m_ldim[i];
        }
    }

  public:
    void reshape(int m) {
        m_nDim = 1;
        m_ldim[0] = m;
        setOffset();
    }
    void reshape(int m, int n) {
        m_nDim = 2;
        m_ldim[0] = m;
        m_ldim[1] = n;
        setOffset();
    }
    void reshape(int m, int n, int k) {
        m_nDim = 3;
        m_ldim[0] = m;
        m_ldim[1] = n;
        m_ldim[2] = k;
        setOffset();
    }
    void reshape(int m, int n, int k, int l) {
        m_nDim = 4;
        m_ldim[0] = m;
        m_ldim[1] = n;
        m_ldim[2] = k;
        m_ldim[3] = l;
        setOffset();
    }

    size_t size() {
        size_t nsz = 1;
        for (int i = 0; i < m_nDim; i++) {
            nsz *= m_ldim[i];
        }
        if (m_nDim == 0)
            nsz = 0;
        return nsz;
    }
    void copyFrom(FTensor<T> &t2) {
        size_t nsz = size();
        assert(nsz == t2.size());
        memcpy(get_ptr(), t2.get_ptr(), nsz * sizeof(T));
    }
    void copyTo(FTensor<T> &t2) {
        size_t nsz = size();
        assert(nsz == t2.size());
        memcpy(t2.get_ptr(), get_ptr(), nsz * sizeof(T));
    }
    void max_abs(FTensor<T> &t2) {
        size_t nsz = size();
        T *ptr2 = t2.get_ptr();
        for (int i = 0; i < nsz; i++) {
            m_ptr[i] = max(std::abs(m_ptr[i]), std::abs(ptr2[i]));
        }
    }
    void add_abs(FTensor<T> &t2) {
        size_t nsz = size();
        T *ptr2 = t2.get_ptr();
        for (size_t i = 0; i < nsz; i++) {
            m_ptr[i] = std::abs(m_ptr[i]) + std::abs(ptr2[i]);
        }
    }
    ~FTensor() {
        if (m_ownptr == 1) {
            // cout << "icnt_ftensor = " << m_counter << endl;
            delete[] m_ptr;
        }
    }
    void set_counter() { ; } // { m_counter = icnt_ftensor; icnt_ftensor++; }
    FTensor() : m_ownptr(0), m_nDim(0), m_ptr(NULL) { set_counter(); }
    FTensor(T *ptr, int m) {
        m_ownptr = 0;
        m_ptr = ptr;
        m_nDim = 1;
        m_ldim[0] = m;
        setOffset();
        set_counter();
    }
    FTensor(T *ptr, int m, int n) {
        m_ownptr = 0;
        m_ptr = ptr;
        m_nDim = 2;
        m_ldim[0] = m;
        m_ldim[1] = n;
        setOffset();
        set_counter();
    }
    FTensor(T *ptr, int m, int n, int k) {
        m_ownptr = 0;
        m_ptr = ptr;
        m_nDim = 3;
        m_ldim[0] = m;
        m_ldim[1] = n;
        m_ldim[2] = k;
        setOffset();
        set_counter();
    }
    FTensor(T *ptr, int m, int n, int k, int l) {
        m_ownptr = 0;
        m_ptr = ptr;
        m_nDim = 4;
        m_ldim[0] = m;
        m_ldim[1] = n;
        m_ldim[2] = k;
        m_ldim[3] = l;
        setOffset();
        set_counter();
    }
    FTensor(T *ptr, int m, int n, int k, int l, int o) {
        m_ownptr = 0;
        m_ptr = ptr;
        m_nDim = 5;
        m_ldim[0] = m;
        m_ldim[1] = n;
        m_ldim[2] = k;
        m_ldim[3] = l;
        m_ldim[4] = o;
        setOffset();
        set_counter();
    }
    FTensor(T *ptr, int nDim, int *ldim) {
        m_ownptr = 0;
        m_ptr = ptr;
        m_nDim = nDim;
        for (int i = 0; i < nDim; i++)
            m_ldim[i] = ldim[i];
        setOffset();
        set_counter();
    }

    FTensor(int m) : m_ownptr(0), m_nDim(0), m_ptr(NULL) { init(m); }
    FTensor(int m, int n) : m_ownptr(0), m_nDim(0), m_ptr(NULL) { init(m, n); }
    FTensor(int m, int n, int k) : m_ownptr(0), m_nDim(0), m_ptr(NULL) {
        init(m, n, k);
    }
    FTensor(int m, int n, int k, int l) : m_ownptr(0), m_nDim(0), m_ptr(NULL) {
        init(m, n, k, l);
    }
    FTensor(int m, int n, int k, int l, int o)
        : m_ownptr(0), m_nDim(0), m_ptr(NULL) {
        init(m, n, k, l, o);
    }

    void init(int m) {
        if (m_ownptr == 1)
            delete[] m_ptr;
        m_ownptr = 1;
        m_ptr = new T[m];
        m_nDim = 1;
        m_ldim[0] = m;
        setOffset();
        memset(m_ptr, 0, sizeof(T) * m);
        set_counter();
    }

    void init(int m, int n) {
        if (m_ownptr == 1)
            delete[] m_ptr;
        m_ownptr = 1;
        m_ptr = new T[m * n];
        m_nDim = 2;
        m_ldim[0] = m;
        m_ldim[1] = n;
        setOffset();
        memset(m_ptr, 0, sizeof(T) * m * n);
        set_counter();
    }
    void init(int m, int n, int k) {
        if (m_ownptr == 1)
            delete[] m_ptr;
        m_ownptr = 1;
        m_ptr = new T[m * n * k];
        m_nDim = 3;
        m_ldim[0] = m;
        m_ldim[1] = n;
        m_ldim[2] = k;
        setOffset();
        memset(m_ptr, 0, sizeof(T) * m * n * k);
        set_counter();
    }
    void init(int m, int n, int k, int l) {
        if (m_ownptr == 1)
            delete[] m_ptr;
        m_ownptr = 1;
        m_ptr = new T[m * n * k * l];
        m_nDim = 4;
        m_ldim[0] = m;
        m_ldim[1] = n;
        m_ldim[2] = k;
        m_ldim[3] = l;
        setOffset();
        memset(m_ptr, 0, sizeof(T) * m * n * k * l);
        set_counter();
    }
    void init(int m, int n, int k, int l, int o) {
        if (m_ownptr == 1)
            delete[] m_ptr;
        m_ownptr = 1;
        m_ptr = new T[m * n * k * l * o];
        m_nDim = 5;
        m_ldim[0] = m;
        m_ldim[1] = n;
        m_ldim[2] = k;
        m_ldim[3] = l;
        m_ldim[4] = o;
        setOffset();
        memset(m_ptr, 0, sizeof(T) * m * n * k * l * o);
        set_counter();
    }
    void init(T *ptr, int m) {
        if (m_ownptr == 1)
            delete[] m_ptr;
        m_ownptr = 0;
        m_ptr = ptr;
        m_nDim = 1;
        m_ldim[0] = m;
        setOffset();
        set_counter();
    }
    void init(T *ptr, int m, int n) {
        if (m_ownptr == 1)
            delete[] m_ptr;
        m_ownptr = 0;
        m_ptr = ptr;
        m_nDim = 2;
        m_ldim[0] = m;
        m_ldim[1] = n;
        setOffset();
        set_counter();
    }
    void init(T *ptr, int m, int n, int k) {
        if (m_ownptr == 1)
            delete[] m_ptr;
        m_ownptr = 0;
        m_ptr = ptr;
        m_nDim = 3;
        m_ldim[0] = m;
        m_ldim[1] = n;
        m_ldim[2] = k;
        setOffset();
        set_counter();
    }
    void init(T *ptr, int m, int n, int k, int l) {
        if (m_ownptr == 1)
            delete[] m_ptr;
        m_ownptr = 0;
        m_ptr = ptr;
        m_nDim = 4;
        m_ldim[0] = m;
        m_ldim[1] = n;
        m_ldim[2] = k;
        m_ldim[3] = l;
        setOffset();
        set_counter();
    }
    void init(T *ptr, int m, int n, int k, int l, int o) {
        if (m_ownptr == 1)
            delete[] m_ptr;
        m_ownptr = 0;
        m_ptr = ptr;
        m_nDim = 5;
        m_ldim[0] = m;
        m_ldim[1] = n;
        m_ldim[2] = k;
        m_ldim[3] = l;
        m_ldim[4] = o;
        setOffset();
        set_counter();
    }

    inline T &operator()(int i) // fortran index, starting from 1
    {
        assert((i - 1) > -1 && (i - 1) < m_ldim[0]);
        return *(m_ptr + i - 1);
    }
    inline T &operator()(int i, int j) // fortran index, starting from 1
    {
        size_t offset = m_offset[0] * (i - 1) + m_offset[1] * (j - 1);
        assert((int)offset > -1 && offset < m_ldim[0] * m_ldim[1]);
        return *(m_ptr + offset);
    }
    inline T &operator()(int i, int j, int k) // fortran index, starting from 1
    {
        size_t offset = m_offset[0] * (i - 1) + m_offset[1] * (j - 1) +
                        m_offset[2] * (k - 1);
        assert((int)offset > -1 && offset < m_ldim[0] * m_ldim[1] * m_ldim[2]);
        return *(m_ptr + offset);
    }
    inline T &operator()(int i, int j, int k,
                         int l) // fortran index, starting from 1
    {
        size_t offset = m_offset[0] * (i - 1) + m_offset[1] * (j - 1) +
                        m_offset[2] * (k - 1) + m_offset[3] * (l - 1);
        assert((int)offset > -1 &&
               offset < m_ldim[0] * m_ldim[1] * m_ldim[2] * m_ldim[3]);
        return *(m_ptr + offset);
    }
    inline T &operator()(int i, int j, int k, int l,
                         int o) // fortran index, starting from 1
    {
        size_t offset = m_offset[0] * (i - 1) + m_offset[1] * (j - 1) +
                        m_offset[2] * (k - 1) + m_offset[3] * (l - 1) +
                        m_offset[4] * (o - 1);
        assert((int)offset > -1 && offset < m_ldim[0] * m_ldim[1] * m_ldim[2] *
                                                m_ldim[3] * m_ldim[4]);
        return *(m_ptr + offset);
    }

    inline T *get_ptr() // fortran index, starting from 1
    {
        return m_ptr;
    }

    inline T *get_ptr(int i) // fortran index, starting from 1
    {
        size_t offset = m_offset[m_nDim - 1] * (i - 1);
        assert((int)offset > -1 && offset < m_ldim[0]);
        return m_ptr + offset;
    }

    inline T *get_ptr(int i, int j) // fortran index, starting from 1
    {
        size_t offset =
            m_offset[m_nDim - 2] * (i - 1) + m_offset[m_nDim - 1] * (j - 1);
        assert((int)offset > -1 && offset < m_ldim[0] * m_ldim[1]);
        return m_ptr + offset;
    }
    inline T *get_ptr(int i, int j, int k) // fortran index, starting from 1
    {
        size_t offset = m_offset[m_nDim - 3] * (i - 1) +
                        m_offset[m_nDim - 2] * (j - 1) +
                        m_offset[m_nDim - 1] * (k - 1);
        assert((int)offset > -1 && offset < m_ldim[0] * m_ldim[1] * m_ldim[2]);
        return m_ptr + offset;
    }
    inline T *get_ptr(int i, int j, int k,
                      int l) // fortran index, starting from 1
    {
        size_t offset =
            m_offset[m_nDim - 4] * (i - 1) + m_offset[m_nDim - 3] * (j - 1) +
            m_offset[m_nDim - 2] * (k - 1) + m_offset[m_nDim - 1] * (l - 1);
        assert((int)offset > -1 &&
               offset < m_ldim[0] * m_ldim[1] * m_ldim[2] * m_ldim[3]);
        return m_ptr + offset;
    }
    inline T *get_ptr(int i, int j, int k, int l,
                      int o) // fortran index, starting from 1
    {
        size_t offset =
            m_offset[m_nDim - 5] * (i - 1) + m_offset[m_nDim - 4] * (j - 1) +
            m_offset[m_nDim - 3] * (k - 1) + m_offset[m_nDim - 2] * (l - 1) +
            m_offset[m_nDim - 1] * (o - 1);
        assert((int)offset > -1 && offset < m_ldim[0] * m_ldim[1] * m_ldim[2] *
                                                m_ldim[3] * m_ldim[4]);
        return m_ptr + offset;
    }

    T abs_sum() {
        T sum = 0.;
        for (size_t i = 0, ns = size(); i < ns; ++i) {
            sum += std::abs(m_ptr[i]);
        }
        return sum;
    }

    void set_offset(int idim, size_t offseti) {
        assert(idim <= this->m_nDim);
        m_offset[idim - 1] = offseti;
    }
};

template <class T> class CTensor : public FTensor<T> {
  public:
    CTensor() : FTensor<T>() { ; }
    CTensor(int m) : FTensor<T>(m) { ; }
    CTensor(int m, int n) : FTensor<T>(m, n) { ; }
    CTensor(int m, int n, int k) : FTensor<T>(m, n, k) { ; }
    CTensor(int m, int n, int k, int l) : FTensor<T>(m, n, k, l) { ; }
    CTensor(int m, int n, int k, int l, int o) : FTensor<T>(m, n, k, l, o) { ; }
    CTensor(int nDim, int *ldim) : FTensor<T>(nDim, ldim) { ; }
    CTensor(T *ptr, int m) : FTensor<T>(ptr, m) { ; }
    CTensor(T *ptr, int m, int n) : FTensor<T>(ptr, m, n) { ; }
    CTensor(T *ptr, int m, int n, int k) : FTensor<T>(ptr, m, n, k) { ; }
    CTensor(T *ptr, int m, int n, int k, int l) : FTensor<T>(ptr, m, n, k, l) {
        ;
    }
    CTensor(T *ptr, int m, int n, int k, int l, int o)
        : FTensor<T>(ptr, m, n, k, l, o) {
        ;
    }
    CTensor(T *ptr, int nDim, int *ldim) : FTensor<T>(ptr, nDim, ldim) { ; }

    void operator=(T a) {
        for (size_t i = 0, nsz = size(); i < nsz; ++i) {
            m_ptr[i] = a;
        }
    }

    inline T &operator()(int i) {
        return *(m_ptr + i);
        assert(i > -1 && i < m_ldim[0]);
    }
    inline T &operator()(int i, int j) {
        size_t offset = m_offset[0] * (i) + m_offset[1] * (j);
        assert((int)offset > -1 && (int)offset < m_ldim[0] * m_ldim[1]);
        return *(m_ptr + offset);
    }
    inline T &operator()(int i, int j, int k) // fortran index, starting from 1
    {
        size_t offset =
            m_offset[0] * (i) + m_offset[1] * (j) + m_offset[2] * (k);
        assert((int)offset > -1 &&
               (int)offset < m_ldim[0] * m_ldim[1] * m_ldim[2]);
        return *(m_ptr + offset);
    }
    inline T &operator()(int i, int j, int k,
                         int l) // fortran index, starting from 1
    {
        size_t offset = m_offset[0] * (i) + m_offset[1] * (j) +
                        m_offset[2] * (k) + m_offset[3] * (l);
        assert((int)offset > -1 &&
               (int)offset < m_ldim[0] * m_ldim[1] * m_ldim[2] * m_ldim[3]);
        return *(m_ptr + offset);
    }
    inline T &operator()(int i, int j, int k, int l,
                         int o) // fortran index, starting from 1
    {
        size_t offset = m_offset[0] * (i) + m_offset[1] * (j) +
                        m_offset[2] * (k) + m_offset[3] * (l) +
                        m_offset[4] * (o);
        assert((int)offset > -1 && (int)offset < m_ldim[0] * m_ldim[1] *
                                                     m_ldim[2] * m_ldim[3] *
                                                     m_ldim[4]);
        return *(m_ptr + offset);
    }
    inline T *get_ptr(int i) // fortran index, starting from 1
    {
        size_t offset = m_offset[m_nDim - 1] * (i);
        assert((int)offset > -1 && (int)offset < m_ldim[0]);
        return m_ptr + offset;
    }

    inline T *get_ptr(int i, int j) // fortran index, starting from 1
    {
        size_t offset = m_offset[m_nDim - 2] * (i) + m_offset[m_nDim - 1] * (j);
        assert((int)offset > -1 && (int)offset < m_ldim[0] * m_ldim[1]);
        return m_ptr + offset;
    }
    inline T *get_ptr(int i, int j, int k) // fortran index, starting from 1
    {
        size_t offset = m_offset[m_nDim - 3] * (i) +
                        m_offset[m_nDim - 2] * (j) + m_offset[m_nDim - 1] * (k);
        assert((int)offset > -1 &&
               (int)offset < m_ldim[0] * m_ldim[1] * m_ldim[2]);
        return m_ptr + offset;
    }
    inline T *get_ptr(int i, int j, int k,
                      int l) // fortran index, starting from 1
    {
        size_t offset = m_offset[m_nDim - 4] * (i) +
                        m_offset[m_nDim - 3] * (j) +
                        m_offset[m_nDim - 2] * (k) + m_offset[m_nDim - 1] * (l);
        assert((int)offset > -1 &&
               (int)offset < m_ldim[0] * m_ldim[1] * m_ldim[2] * m_ldim[3]);
        return m_ptr + offset;
    }
    inline T *get_ptr(int i, int j, int k, int l,
                      int o) // fortran index, starting from 1
    {
        size_t offset = m_offset[m_nDim - 5] * (i) +
                        m_offset[m_nDim - 4] * (j) +
                        m_offset[m_nDim - 3] * (k) +
                        m_offset[m_nDim - 2] * (l) + m_offset[m_nDim - 1] * (o);
        assert((int)offset > -1 && (int)offset < m_ldim[0] * m_ldim[1] *
                                                     m_ldim[2] * m_ldim[3] *
                                                     m_ldim[4]);
        return m_ptr + offset;
    }
};
