import ctypes

lib = ctypes.cdll.LoadLibrary("target/debug/librust.so")
print(lib.addition(1, 2))
