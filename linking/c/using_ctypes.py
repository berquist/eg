import ctypes


if __name__ == "__main__":

    mylib = ctypes.CDLL("build/libmylib.so")
    print(mylib.add1(4))

    # Soe mice instructions are in
    # https://stackoverflow.com/questions/26277322/passing-arrays-with-ctypes

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
    # https://stackoverflow.com/questions/4145775/how-do-i-convert-a-python-list-into-a-c-array-by-using-ctypes
    cx = (ctypes.c_double * n)(*x)
    cy = (ctypes.c_double * n)(*y)
    daxpy(n, ctypes.c_double(alpha), cx, cy)
    assert list(y) == [1.0, 1.0, 1.0]
    assert list(cy) == [3.0, 4.0, 5.0]
