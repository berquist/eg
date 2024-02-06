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


# Not sure why this doesn't work.
# #pythran export rank4_simple_pythran(float64 [:,:,:,:], float64 [:,:,:,;])
# def rank4_simple_pythran(a, b):
#     return rank4_simple(a, b)


# pythran export rank4_simple2_pythran(float64 [:,:,:,:], float64 [:,:,:,:])
def rank4_simple2_pythran(a, b):
    assert a.shape == b.shape
    da, db, dc, dd = a.shape
    s = 0
    for iia in range(da):
        for iib in range(db):
            for iic in range(dc):
                for iid in range(dd):
                    s += a[iia, iib, iic, iid] * b[iia, iib, iic, iid]
    return s
