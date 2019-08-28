from libc.stdlib cimport malloc, free

import numpy as np
cimport numpy as np

cimport using_cython


def cython_dgemm():
    n = 3
    l = 4
    m = 5
    npx = np.empty((n, m))
    npx.fill(2.0)
    npy = np.empty((m, l))
    npy.fill(3.0)
    cdef const double [:] vx = npx.reshape((-1))
    cdef const double [:] vy = npy.reshape((-1))
    # Rather than do this an allocate Python-side, ...
    # npz = np.empty((n, l))
    # cdef double [:] vz = npz.reshape((-1))    
    # using_cython.dgemm(n, l, m, &vx[0], &vy[0], &vz[0])
    # ...do it C-side.
    cdef double* z = <double *> malloc(sizeof(double) * (n * l))
    using_cython.dgemm(n, l, m, &vx[0], &vy[0], z)
    npz = np.asarray(<double[:n, :l]>z)
    print(npz)
    npz2 = npz.copy()
    free(z)
    # This looks at freed memory!
    # print(npz)
    # This doesn't.
    print(npz2)
