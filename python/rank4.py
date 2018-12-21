def rank4_simple(a, b):
    assert a.shape == b.shape
    da, db, dc, dd = a.shape
    s = 0
    for iia in range(da):
        for iib in range(db):
            for iic in range(dc):
                for iid in range(dd):
                    s += a[iia, iib, iic, iid] * b[iia, iib, iic, iid]
    return s
