#ifndef BIND_H
#define BIND_H

#include <complex.h>

/*!
 * @brief absolute difference between to complex numbers.
 * @param ref: reference value.
 * @param comp: comparison value.
 * @return sqrt(rev - comp)
 */
double errAbs(double complex ref, double complex comp);

/*!
 * @brief relative difference between to complex numbers.
 * @param ref: reference value.
 * @param comp: comparison value.
 * @return errAbs / norm(ref)
 */
double errRel(double complex ref, double complex comp);

#endif /* BIND_H */
