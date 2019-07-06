import sys
import ctypes

from ctypes import c_uint32


lib = ctypes.cdll.LoadLibrary("target/debug/librust.so")
print(lib.addition(1, 2))
