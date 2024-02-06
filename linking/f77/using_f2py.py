import mylib_f77
import numpy as np

if __name__ == "__main__":
    x = [2.0, 3.0, 4.0]
    y = [1.0, 1.0, 1.0]
    alpha = 1.0
    n = len(x)
    # Functions can take iterables, but you get an ndarray back. You also
    # modify an argument inplace if it isn't an ndarray.
    ret = mylib_f77.daxpy(n, alpha, x, y)
    assert y == [1.0, 1.0, 1.0]
    assert isinstance(ret, np.ndarray)
    ref = np.array([3.0, 4.0, 5.0])
    np.testing.assert_equal(ret, ref)

    # switch from intent(in,out) to intent(inout)
    y = np.array([1.0, 1.0, 1.0])
    ret = mylib_f77.daxpy_inplace(n, alpha, x, y)
    np.testing.assert_equal(y, ref)
    assert ret == None
