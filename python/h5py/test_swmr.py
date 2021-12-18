import numpy as np
import h5py

FNAME_NO = "big_swmr_no.h5"
FNAME_YES = "big_swmr_yes.h5"
dim = int(1.5e3)
print(f"allocating {(8 / 1_000_000) * (dim ** 3)} megabyte ndarray...")
x = np.random.random((dim, dim, dim))
y = np.random.random((dim, dim, dim))
print("done NumPy alloc")

# h5file_no = h5py.File(FNAME_NO, mode="w", libver="latest")
# h5file_no["x"] = x
# print("done HDF5 write")

h5file_yes = h5py.File(FNAME_YES, mode="w", libver="latest")
h5file_yes["x"] = x
print("performing update...")
h5file_yes.swmr_mode = True
h5file_yes["x"][()] = y
print("done HDF5 write")
