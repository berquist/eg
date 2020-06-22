"""Examples adapted from https://stackoverflow.com/a/41754104/3249688"""

import copyreg
import pickle


class A:
    """Default getstate and setstate"""
    def __init__(self, i):
        self.i = i


class Z:
    """Default getstate and setstate"""
    def __init__(self, i):
        self.i = i


# copyreg.pickle(Z, lambda z: Z, z.i)
def pickle_z(z):
    return Z, (z.i, )
copyreg.pickle(Z, pickle_z)


class B:
    """Default setstate"""
    def __init__(self, i):
        self.i = i
    def __eq__(self, other):
        return self.i == other.i
    def __getstate__(self):
        print(f"calling __getstate__ for {type(self)}")
        return {"i": self.i}


class C:
    """Default getstate"""
    def __init__(self, i):
        self.i = i
    def __eq__(self, other):
        return self.i == other.i
    def __setstate__(self, state):
        print(f"calling __setstate__ for {type(self)}")
        self.i = state["i"]


class D:
    def __init__(self, i):
        self.i = i
    def __eq__(self, other):
        return self.i == other.i
    def __getstate__(self):
        print(f"calling __getstate__ for {type(self)}")
        return self.i
    def __setstate__(self, state):
        print(f"calling __setstate__ for {type(self)}")
        self.i = state


class E:
    """Both defaults with __slots__"""
    __slots__ = "i"
    def __init__(self, i):
        self.i = i
    def __eq__(self, other):
        return self.i == other.i


class F:
    """Default setstate with __slots__"""
    __slots__ = "i"
    def __init__(self, i):
        self.i = i
    def __eq__(self, other):
        return self.i == other.i
    def __getstate__(self):
        print(f"calling __getstate__ for {type(self)}")
        return {slot: getattr(self, slot) for slot in self.__slots__}


class G:
    """Default getstate with __slots__"""
    __slots__ = "i"
    def __init__(self, i):
        self.i = i
    def __eq__(self, other):
        return self.i == other.i
    def __setstate__(self, state):
        print(f"calling __setstate__ for {type(self)}")
        for slot in state:
            setattr(self, slot, state[slot])


if __name__ == "__main__":

    print("=" * 70)

    print(pickle.dumps(A(1)))
    print(pickle.dumps(Z(1)))
    print(pickle.dumps(B(1)))
    print(pickle.dumps(C(1)))
    print(pickle.dumps(D(1)))
    print(pickle.dumps(E(1)))
    print(pickle.dumps(F(1)))
    print(pickle.dumps(G(1)))

    print("=" * 70)

    print(pickle.loads(pickle.dumps(A(1))))
    print(pickle.loads(pickle.dumps(Z(1))))
    print(pickle.loads(pickle.dumps(B(1))))
    print(pickle.loads(pickle.dumps(C(1))))
    print(pickle.loads(pickle.dumps(D(1))))
    print(pickle.loads(pickle.dumps(E(1))))
    print(pickle.loads(pickle.dumps(F(1))))
    print(pickle.loads(pickle.dumps(G(1))))

    print("=" * 70)

    print(pickle.loads(pickle.dumps(A(1))).i)
    print(pickle.loads(pickle.dumps(Z(1))).i)
    print(pickle.loads(pickle.dumps(B(1))).i)
    print(pickle.loads(pickle.dumps(C(1))).i)
    print(pickle.loads(pickle.dumps(D(1))).i)
    print(pickle.loads(pickle.dumps(E(1))).i)
    print(pickle.loads(pickle.dumps(F(1))).i)
    print(pickle.loads(pickle.dumps(G(1))).i)

    print(hash(A(1)))
    print(hash(pickle.loads(pickle.dumps(A(1)))))
    print(hash(Z(1)))
    print(hash(pickle.loads(pickle.dumps(Z(1)))))
    print(hash(B(1)))
    print(hash(pickle.loads(pickle.dumps(B(1)))))
    print(hash(C(1)))
    print(hash(pickle.loads(pickle.dumps(C(1)))))
    print(hash(D(1)))
    print(hash(pickle.loads(pickle.dumps(D(1)))))
    print(hash(E(1)))
    print(hash(pickle.loads(pickle.dumps(E(1)))))
    print(hash(F(1)))
    print(hash(pickle.loads(pickle.dumps(F(1)))))
    print(hash(G(1)))
    print(hash(pickle.loads(pickle.dumps(G(1)))))

    assert pickle.loads(pickle.dumps(A(1))) == A(1)
    assert pickle.loads(pickle.dumps(Z(1))) == Z(1)
    assert pickle.loads(pickle.dumps(B(1))) == B(1)
    assert pickle.loads(pickle.dumps(C(1))) == C(1)
    assert pickle.loads(pickle.dumps(D(1))) == D(1)
    assert pickle.loads(pickle.dumps(E(1))) == E(1)
    assert pickle.loads(pickle.dumps(F(1))) == F(1)
    assert pickle.loads(pickle.dumps(G(1))) == G(1)
