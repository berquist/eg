from mylib_f77 import daxpy


if __name__ == "__main__":

    print(daxpy)

    x = [2.0, 3.0, 4.0]
    y = [1.0, 1.0, 1.0]
    alpha = 1.0
    n = len(x)
    ret = daxpy(n, alpha, x, y)
    print(ret)
    print(type(ret))
    print(y)
    # assert list(y) == [1.0, 1.0, 1.0]
