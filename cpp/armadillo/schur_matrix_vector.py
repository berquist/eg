#!/usr/bin/env python

import numpy as np

dim = 3

A = np.ones(shape=(dim, dim))
B = A.copy()
b = np.empty(dim)
for i in range(dim):
    b[i] = i + 2

print("A")
print(A)
print("b")
print(b)

for j in range(dim):
    A[:, j] *= b[j]
print("% (1)")
print(A)

print("% (2)")
print(B * b)
