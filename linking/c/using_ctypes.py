from ctypes import CDLL

mylib = CDLL("build/libmylib.so")
print(mylib.add1(4))
