// def rank4_simple2_pythran(a, b):
//     assert a.shape == b.shape
//     da, db, dc, dd = a.shape
//     s = 0
//     for iia in range(da):
//         for iib in range(db):
//             for iic in range(dc):
//                 for iid in range(dd):
//                     s += a[iia, iib, iic, iid] * b[iia, iib, iic, iid]
//     return s

#include "xtensor/xtensor.hpp"

double rank4_simple(xt::xtensor<double, 4> &a, xt::xtensor<double, 4> &b) {
    double s = 0.0;

    return s;
}
