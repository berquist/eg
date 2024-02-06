import pickle
from copy import copy

from immutablecollections import (
    ImmutableSet,
    immutabledict,
    immutablelistmultidict,
    immutableset,
    immutablesetmultidict,
)


def pickle_immutableset(s):
    print("pickling an immutableset...")
    if hasattr(s, "_single_value"):
        items = (s._single_value,)
    else:
        items = s._iteration_order
    return ImmutableSet, items


if __name__ == "__main__":
    s1 = immutableset([5])
    s2 = immutableset([5, 2])

    print(isinstance(s1, ImmutableSet))
    print(isinstance(s2, ImmutableSet))

    s1_bytes = pickle.dumps(s1)
    s2_bytes = pickle.dumps(s2)
    print(s1_bytes)
    print(s2_bytes)

    s1_hydrated = pickle.loads(s1_bytes)
    s2_hydrated = pickle.loads(s2_bytes)
    print(id(s1_hydrated))
    print(id(s2_hydrated))

    # copyreg.pickle(ImmutableSet, pickle_immutableset, immutableset)

    # s1_bytes_mod = pickle.dumps(s1)
    # s2_bytes_mod = pickle.dumps(s2)
    # print(s1_bytes_mod)
    # print(s2_bytes_mod)

    # s1_hydrated_mod = pickle.loads(s1_bytes_mod)
    # s2_hydrated_mod = pickle.loads(s2_bytes_mod)
    # print(id(s1_hydrated_mod))
    # print(id(s2_hydrated_mod))

    # assert s1_hydrated == s1_hydrated_mod
    # assert s2_hydrated == s2_hydrated_mod

    d = immutabledict([(1, (2, 2, 3, 6)), (4, (5, 6))])
    smd = immutablesetmultidict([(1, (2, 2, 3, 6)), (4, (5, 6))])
    lmd = immutablelistmultidict([(1, (2, 2, 3, 6)), (4, (5, 6))])
    for k, vg in smd.items():
        for v in vg:
            print(k, v)
    print(list(d.items()))
    print(list(smd.items()))
    print(list(lmd.items()))

    print(pickle.dumps(d))
    print(pickle.dumps(smd))
    print(pickle.dumps(lmd))

    d2 = copy(d)
    smd2 = copy(smd)
    lmd2 = copy(lmd)

    assert id(d) != id(d2)
    assert d == d2
    assert id(smd) != id(smd2)
    assert smd == smd2
    assert id(lmd) != id(lmd2)
    assert lmd == lmd2
