import h5py


FNAME = "lists_and_strings.h5"

h5file = h5py.File(FNAME, mode="w", libver="latest")

l1 = [43, 44, 29]
# h5file["l1"] = l1
# l1.append(99)
# h5file["l1"] = l1
dset_l1 = h5file.create_dataset("l1", data=l1, maxshape=(None,))
print(dset_l1[()])
l1.append(99)
dset_l1.resize((len(l1),))
dset_l1[()] = l1
print(dset_l1[()])

l2 = ["apple", "pear", "banana"]
h5file["l2"] = l2

s1 = "hello world"
h5file["s1"] = s1
s2 = "how are you"
# "scalar datasets cannot be extended"
# dset_s2 = h5file.create_dataset("s2", data=s2, maxshape=(None,))
