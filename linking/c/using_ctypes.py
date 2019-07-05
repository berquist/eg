import ctypes

if __name__ == "__main__":

    mylib = ctypes.CDLL("build/libmylib.so")
    print(mylib.add1(4))

    daxpy = mylib.daxpy
    daxpy.argypes = [
        ctypes.c_size_t,
        ctypes.c_double,
        ctypes.POINTER(ctypes.c_double),
        ctypes.POINTER(ctypes.c_double),
    ]
    daxpy.restype = None

    x = [2.0, 3.0, 4.0]
    y = [1.0, 1.0, 1.0]
    alpha = 1.0
    n = len(x)
    cx = (ctypes.c_double * n)(*x)
    cy = (ctypes.c_double * n)(*y)
    daxpy(n, ctypes.c_double(alpha), cx, cy)
    assert list(y) == [1.0, 1.0, 1.0]
    assert list(cy) == [3.0, 4.0, 5.0]
